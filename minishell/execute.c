/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:39:38 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 20:18:18 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*find_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*path_line;
	char	*full_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path_line = envp[i] + 5;
	paths = ft_split(path_line, ':');
	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

void	execute_external(char **args, char **envp)
{
	pid_t	pid;
	char	*path;

	if (!args[0])
		return ;
	if (access(args[0], X_OK) == 0)
		path = ft_strdup(args[0]);
	else
		path = find_executable(args[0], envp);
	if (!path)
	{
		printf("%s: command not found\n", args[0]);
		return ;
	}
	pid = fork();
	if (pid == 0)
		execve(path, args, envp);
	else
		waitpid(pid, NULL, 0);
	free(path);
}
