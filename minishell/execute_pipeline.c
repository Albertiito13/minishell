/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:00:53 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/03 17:01:35 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(char **segments, char **my_env)
{
	int		fd[2];
	int		in_fd;
	pid_t	pid;
	int		i;
	char	**args;
	char	*path;

	in_fd = 0;
	i = 0;
	while (segments[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(in_fd, 0);
			if (segments[i + 1])
				dup2(fd[1], 1);
			close(fd[0]);
			args = parse_line(segments[i]);
			if (!args || !args[0])
				exit(0);
			if (access(args[0], X_OK) == 0)
				path = ft_strdup(args[0]);
			else
				path = find_executable(args[0], my_env);
			if (!path)
			{
				printf("%s: command not found\n", args[0]);
				exit(127);
			}
			execve(path, args, my_env);
		}
		else
		{
			wait(NULL);
			close(fd[1]);
			in_fd = fd[0];
		}
		i++;
	}
}
