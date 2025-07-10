/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:15:15 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/10 22:33:23 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*extract_key(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (ft_substr(arg, 0, len));
}

static void	update_env(char *arg, char ***env, int key_len)
{
	int		j;
	char	**new_env;

	j = 0;
	while ((*env)[j])
	{
		if (ft_strncmp((*env)[j], arg, key_len) == 0
			&& (*env)[j][key_len] == '=')
		{
			free((*env)[j]);
			(*env)[j] = ft_strdup(arg);
			return ;
		}
		j++;
	}
	new_env = add_to_env(*env, arg);
	if (!new_env)
		return ;
	free_split(*env);
	*env = new_env;
}

static void	add_env_entry(char *arg, char ***env)
{
	char	**new_env;

	new_env = add_to_env(*env, arg);
	if (!new_env)
		return ;
	free_split(*env);
	*env = new_env;
}

void	handle_export_arg(char *arg, char ***my_env)
{
	char	*key;
	int		key_len;
	char	*entry;

	key = extract_key(arg);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("`: not a valid identifier\n", 2);
		g_exit_status = 1;
		free(key);
		return ;
	}
	key_len = ft_strlen(key);
	free(key);
	if (!arg[key_len])
	{
		entry = ft_strjoin(arg, "=");
		add_env_entry(entry, my_env);
		free(entry);
	}
	else
		update_env(arg, my_env, key_len);
}

void	builtin_export(char **args, char ***my_env)
{
	int	i;

	if (!args[0])
	{
		print_sorted_env(*my_env);
		return ;
	}
	i = 0;
	while (args[i])
	{
		handle_export_arg(args[i], my_env);
		i++;
	}
}
