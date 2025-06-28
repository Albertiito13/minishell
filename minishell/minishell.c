/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:47:42 by albcamac          #+#    #+#             */
/*   Updated: 2025/06/28 16:53:35 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
    (void)argc;
    (void)argv;

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
				builtin_env(envp);
			else if (ft_strncmp(args[0], "exit", 5) == 0)
				builtin_exit(&args[1]);
		}
		free_split(args);
		free(line);
	}
	return (0);
}
