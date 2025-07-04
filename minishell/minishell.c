/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:47:42 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 03:04:55 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

// para detectar que es un pipe y no entre en conflicto con ||
static int	has_simple_pipe(char **args)
{
	int i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "|", 2) == 0)
			return (1);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = dup_env(envp);

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		char *expanded = expand_var(line, my_env);
		args = parse_line(expanded);
		free(expanded);
		if (args && args[0])
		{
			if (has_simple_pipe(args))
			{
				char **segments = ft_split(line, '|');
				execute_pipeline(segments, my_env);
				free_split(segments);
			}
			else if (ft_strncmp(args[0], "echo", 5) == 0)
				builtin_echo(&args[1]);
			else if (ft_strncmp(args[0], "pwd", 4) == 0)
				builtin_pwd();
			else if (ft_strncmp(args[0], "env", 4) == 0)
				builtin_env(my_env);
			else if (ft_strncmp(args[0], "unset", 6) == 0)
				builtin_unset(&args[1], &my_env);
			else if (ft_strncmp(args[0], "export", 7) == 0)
				builtin_export(&args[1], &my_env);
			else if (ft_strncmp(args[0], "cd", 3) == 0)
				builtin_cd(&args[1], my_env);
			else if (ft_strncmp(args[0], "exit", 5) == 0)
				builtin_exit(&args[1]);
			else
				execute_external(args, my_env);
		}
		free_split(args);
		free(line);
	}
	free_split(my_env);
	return (0);
}
