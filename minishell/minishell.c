/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:47:42 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/14 22:23:50 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

static void	run_external_command(t_cmd *cmd, char ***env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		setup_exec_signals();
		execute_external(cmd->argv, *env);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		setup_prompt_signals();
		check_child_signal(status);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 128 + WTERMSIG(status);
	}
}

static void	execute_command(t_cmd *cmd, char ***env)
{
	if (!cmd->argv || !cmd->argv[0] || cmd->argv[0][0] == '\0')
		return ;
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		builtin_echo(&cmd->argv[1]);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
	{
		if (cmd->argv[1])
			return ((void)(ft_putstr_fd("Not such file or descriptor\n", 2),
				g_exit_status = 127));
		builtin_env(*env);
	}
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		builtin_unset(&cmd->argv[1], env);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		builtin_export(&cmd->argv[1], env);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		builtin_cd(&cmd->argv[1], *env);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		builtin_exit(&cmd->argv[1]);
	else
		run_external_command(cmd, env);
}

static void	process_command(char **args, char ***env, char *line)
{
	t_cmd	*cmd;
	char	**segments;
	int		saved_stdin;
	int		saved_stdout;

	if (has_simple_pipe(args))
	{
		segments = ft_split(line, '|');
		execute_pipeline(segments, *env);
		free_split(segments);
	}
	else
	{
		cmd = parse_command(args);
		if (!cmd)
			return ;
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (apply_redirections(cmd->redirs, *env) == 0)
			execute_command(cmd, env);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		(close(saved_stdin), close(saved_stdout));
		free_cmd(cmd);
	}
}

static void	main_loop(char ***env)
{
	char	*line;
	char	**args;
	char	*expanded;

	rl_bind_key('\t', NULL);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (line)
			add_history(line);
		expanded = expand_var(line, *env);
		args = parse_line(expanded);
		free(expanded);
		if (args && args[0])
			process_command(args, env, line);
		free_split(args);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_env;

	(void)argc;
	(void)argv;
	if (!envp || !*envp)
		my_env = create_default_env();
	else
		my_env = dup_env(envp);
	increment_shlvl(&my_env);
	setup_prompt_signals();
	main_loop(&my_env);
	free_split(my_env);
	return (0);
}
