/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:14:38 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/08 17:10:14 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

static int	should_unset(char *env_var, char **args)
{
	int		k;
	size_t	len;

	k = 0;
	while (args[k])
	{
		len = ft_strlen(args[k]);
		if (ft_strncmp(env_var, args[k], len) == 0
			&& env_var[len] == '=')
			return (1);
		k++;
	}
	return (0);
}

static char	**filter_env(char **env, char **args)
{
	char	**new_env;
	int		count;
	int		i;
	int		j;

	count = count_env(env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!should_unset(env[i], args))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

void	builtin_unset(char **args, char ***my_env)
{
	char	**new_env;

	new_env = filter_env(*my_env, args);
	if (!new_env)
		return ;
	free_split(*my_env);
	*my_env = new_env;
	g_exit_status = 0;
}
