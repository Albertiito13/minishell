/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:47:42 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/02 23:24:45 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	char	**my_env;

	(void)argc;
	(void)argv;
	my_env = dup_env(envp);
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
		args = parse_line(line);
		if (args && args[0])
		{
			if (ft_strncmp(args[0], "echo", 5) == 0)
				builtin_echo(&args[1]);
			else if (ft_strncmp(args[0], "pwd", 4) == 0)
				builtin_pwd();
			else if (ft_strncmp(args[0], "env", 4) == 0)
				builtin_env(my_env);
			else if (ft_strncmp(args[0], "unset", 6) == 0)
				builtin_unset(&args[1], &my_env);
			else if (ft_strncmp(args[0], "cd", 3) == 0)
				builtin_cd(&args[1], my_env);
			else if (ft_strncmp(args[0], "exit", 5) == 0)
				builtin_exit(&args[1]);
		}
		free_split(args);
		free(line);
	}
	free_split(my_env);
	return (0);
}
