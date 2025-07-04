/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:22:05 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 03:20:35 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 0;
	newline = 1;
	if (args[0] && ft_strncmp(args[0], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}

void	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
}

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}

void	builtin_exit(char **args)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	if (args[0])
	{
		i = 0;
		if (args[0][0] == '-' || args[0][0] == '+')
			i++;
		while (args[0][i] && ft_isdigit(args[0][i]))
			i++;
		if (args[0][i] != '\0') // no es numérico
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[0], 2);
			ft_putstr_fd(": se requiere un argumento numérico\n", 2);
			exit(2);
		}
		if (args[1])
		{
			ft_putstr_fd("exit: demasiados argumentos\n", 2);
			g_exit_status = 1;
			return ;
		}
		exit(ft_atoi(args[0]) % 256);
	}
	exit(0);
}


void	builtin_cd(char **args, char **envp)
{
	char	*path;
	char	*home;

	(void)envp;
	if (args[0] && args[1])
	{
		ft_putstr_fd("cd: demasiados argumentos\n", 2);
		g_exit_status = 1;
		return ;
	}
	path = NULL;
	home = NULL;
	if (!args[0])
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
		path = home;
	}
	else
		path = args[0];
	if (chdir(path) != 0)
	{
		perror("cd");
		g_exit_status = 1;
	}
}

void	builtin_unset(char **args, char ***my_env)
{
	int		i;
	int		j;
	int		count;
	char	**new_env;
	int		k;

	count = 0;
	while ((*my_env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return ;
	i = 0;
	j = 0;
	while ((*my_env)[i])
	{
		k = 0;
		while (args[k])
		{
			if (ft_strncmp((*my_env)[i], args[k], ft_strlen(args[k])) == 0
				&& (*my_env)[i][ft_strlen(args[k])] == '=')
				break ;
			k++;
		}
		if (!args[k])
			new_env[j++] = ft_strdup((*my_env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free_split(*my_env);
	*my_env = new_env;
	g_exit_status = 0;
}


//valida la que la entrada del export sea valida
static int	is_valid_identifier(char *s)
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


void	builtin_export(char **args, char ***my_env)
{
	int		i;
	int		len;
	int		j;
	char	*entry;
	char	**new_env;
	char	*key;

	i = 0;
	while (args[i])
	{
		len = 0;
		while (args[i][len] && args[i][len] != '=')
			len++;
		key = ft_substr(args[i], 0, len);
		if (!is_valid_identifier(key))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("`: not a valid identifier\n", 2);
			g_exit_status = 1;
			free(key);
			i++;
			continue ;
		}
		free(key);
		if (!args[i][len]) // no hay '='
		{
			entry = ft_strjoin(args[i], "=");
			new_env = add_to_env(*my_env, entry);
			free(entry);
		}
		else
		{
			j = 0;
			while ((*my_env)[j])
			{
				if (ft_strncmp((*my_env)[j], args[i], len) == 0
					&& (*my_env)[j][len] == '=')
				{
					free((*my_env)[j]);
					(*my_env)[j] = ft_strdup(args[i]);
					break ;
				}
				j++;
			}
			if (!(*my_env)[j])
				new_env = add_to_env(*my_env, args[i]);
		}
		if (new_env)
		{
			free_split(*my_env);
			*my_env = new_env;
		}
		i++;
	}
}
