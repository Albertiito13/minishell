/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:53 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/08 22:24:29 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child_cmd(t_cmd *cmd, char **my_env)
{
	char	*path;

	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	if (is_builtin(cmd->argv))
	{
		execute_builtin_in_child(cmd->argv, &my_env);
		exit(0);
	}
	if (access(cmd->argv[0], X_OK) == 0)
		path = ft_strdup(cmd->argv[0]);
	else
		path = find_executable(cmd->argv[0], my_env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, my_env);
	if (execve(path, cmd->argv, my_env) == -1)
	{
		perror("execve");
		exit(126);
	}
}

void	run_cmd_in_child(char *seg, int in_fd, int *fd, char **my_env)
{
	char	**tokens;
	t_cmd	*cmd;

	dup2(in_fd, 0);
	if (fd != NULL)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (in_fd != 0)
		close(in_fd);
	tokens = parse_line(seg);
	cmd = parse_command(tokens);
	if (!cmd)
		exit(1);
	if (apply_redirections(cmd->redirs))
		exit(1);
	setup_exec_signals();
	exec_child_cmd(cmd, my_env);
}

static int	create_child(char *segment, int in_fd, int *fd, char **my_env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		run_cmd_in_child(segment, in_fd, fd, my_env);
	return (pid);
}

static pid_t	setup_pipe_and_fork(char *segment, int *in_fd,
						int has_next, char **my_env)
{
	int		fd[2];
	pid_t	pid;

	if (has_next)
	{
		pipe(fd);
		pid = create_child(segment, *in_fd, fd, my_env);
		close(fd[1]);
		if (*in_fd != 0)
			close(*in_fd);
		*in_fd = fd[0];
	}
	else
	{
		pid = create_child(segment, *in_fd, NULL, my_env);
		if (*in_fd != 0)
			close(*in_fd);
	}
	return (pid);
}

void	execute_pipeline(char **segments, char **my_env)
{
	int		in_fd;
	int		i;
	pid_t	last_pid;

	in_fd = 0;
	i = 0;
	while (segments[i])
	{
		last_pid = setup_pipe_and_fork(segments[i], &in_fd,
				segments[i + 1] != NULL, my_env);
		i++;
	}
	wait_pipeline(last_pid);
}
