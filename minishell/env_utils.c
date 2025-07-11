/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:05:31 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/11 16:28:01 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**dup_env(char **envp)
{
	int		size;
	int		i;
	char	**new_env;

	size = env_size(envp);
	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**add_to_env(char **env, char *new_var)
{
	int		size;
	int		i;
	char	**new_env;

	size = env_size(env);
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	*get_env_value(char *var, char **my_env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (my_env && my_env[i])
	{
		if (ft_strncmp(my_env[i], var, len) == 0 && my_env[i][len] == '=')
			return (my_env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	increment_shlvl(char ***my_env)
{
	char	*shlvl_val;
	int		shlvl_num;
	char	*new_shlvl_str;
	char	*new_entry;

	shlvl_val = get_env_value("SHLVL", *my_env);
	if (shlvl_val)
		shlvl_num = ft_atoi(shlvl_val) + 1;
	else
		shlvl_num = 1;
	new_shlvl_str = ft_itoa(shlvl_num);
	new_entry = ft_strjoin("SHLVL=", new_shlvl_str);
	free(new_shlvl_str);
	handle_export_arg(new_entry, my_env);
	free(new_entry);
}
