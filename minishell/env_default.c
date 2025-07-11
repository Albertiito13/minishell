/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_default.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:08:22 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/11 16:39:30 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_default_env(void)
{
	char	**env;
	char	cwd[1024];
	char	*pwd_var;

	if (!getcwd(cwd, sizeof(cwd)))
		return (NULL);
	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = ft_strdup("PATH=/usr/bin:/bin");
	pwd_var = malloc(5 + ft_strlen(cwd) + 1);
	ft_strcpy(pwd_var, "PWD=");
	ft_strcpy(pwd_var + 4, cwd);
	env[1] = pwd_var;
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = (NULL);
	return (env);
}
