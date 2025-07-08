/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:14:03 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/08 17:21:10 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_home_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_exit_status = 1;
		return (NULL);
	}
	return (home);
}

void	builtin_cd(char **args, char **envp)
{
	char	*path;

	(void)envp;
	if (args[0] && args[1])
	{
		ft_putstr_fd("cd: demasiados argumentos\n", 2);
		g_exit_status = 1;
		return ;
	}
	if (!args[0])
		path = get_home_path();
	else
		path = args[0];
	if (!path)
		return ;
	if (chdir(path) != 0)
	{
		perror("cd");
		g_exit_status = 1;
	}
}
