/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:48:53 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/10 22:20:04 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	swap_strs(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**copy_env(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	sort_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				swap_strs(&env[i], &env[j]);
			j++;
		}
		i++;
	}
}

void	print_sorted_env(char **env)
{
	char	**copy;
	int		i;

	copy = copy_env(env);
	if (!copy)
		return ;
	sort_env(copy);
	i = 0;
	while (copy[i])
	{
		if (ft_strchr(copy[i], '='))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(copy[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	free_split(copy);
}
