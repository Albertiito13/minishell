/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:22:05 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/03 00:05:03 by albcamac         ###   ########.fr       */
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
	int	status;

	status = 0;
	ft_printf("exit\n");
	if (args[0])
	{
		status = ft_atoi(args[0]);
		// opcional: podrías validar que es solo dígitos
	}
	exit(status);
}

void	builtin_cd(char **args, char **envp)
{
	char	*path;
	char	*home;

	(void)envp;
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
		perror("cd");
}

void	builtin_unset(char **args, char ***my_env)
{
	int		i;
	char	**new_env;
	int		j;
	int		count;

	i = 0;
	while (args[i])
	{
		count = 0;
		while ((*my_env)[count])
			count++;
		new_env = malloc(sizeof(char *) * (count));
		if (!new_env)
			return ;
		j = 0;
		count = 0;
		while ((*my_env)[count])
		{
			if (ft_strncmp((*my_env)[count], args[i],
					ft_strlen(args[i])) != 0
				|| (*my_env)[count][ft_strlen(args[i])] != '=')
				new_env[j++] = ft_strdup((*my_env)[count]);
			count++;
		}
		new_env[j] = NULL;
		free_split(*my_env);
		*my_env = new_env;
		i++;
	}
}

void	builtin_export(char **args, char ***my_env)
{
	int		i;
	int		len;
	int		j;
	char	**new_env;

	i = 0;
	while (args[i])
	{
		len = 0;
		while (args[i][len] && args[i][len] != '=')
			len++;
		if (!args[i][len])
		{
			printf("export: invalid format: %s\n", args[i]);
			i++;
			continue ;
		}
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
		{
			new_env = add_to_env(*my_env, args[i]);
			free_split(*my_env);
			*my_env = new_env;
		}
		i++;
	}
}


