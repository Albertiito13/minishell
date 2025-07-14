/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:14:03 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/14 22:55:32 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(char **envp, const char *name, const char *value)
{
	int		i;
	char	*tmp;
	size_t	len;

	len = ft_strlen(name);
	tmp = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			tmp = ft_strjoin(name, "=");
			envp[i] = ft_strjoin(tmp, value);
			free(tmp);
			return ;
		}
		i++;
	}
}

void	builtin_cd(char **args, char **envp)
{
	char	cwd[4096];
	char	*path;

	if (args[0] && args[1])
		return ((void)(ft_putstr_fd("cd: demasiados argumentos\n", 2),
			g_exit_status = 1));
	if (!getcwd(cwd, sizeof(cwd)))
		return ((void)(perror("getcwd"), g_exit_status = 1));
	path = args[0];
	if (!path)
		path = getenv("HOME");
	if (!path)
		return ((void)(ft_putstr_fd("cd: HOME not set\n", 2),
			g_exit_status = 1));
	if (chdir(path) != 0)
		return ((void)(perror("cd"), g_exit_status = 1));
	if (getcwd(cwd, sizeof(cwd)))
		update_env(envp, "PWD", cwd);
}
