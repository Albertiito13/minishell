/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 22:14:39 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/10 15:34:34 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

void	execute_builtin_in_child(char **args, char ***my_env)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		builtin_echo(&args[1]);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		builtin_pwd();
	else if (ft_strncmp(args[0], "env", 4) == 0)
		builtin_env(*my_env);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		builtin_unset(&args[1], my_env);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		builtin_export(&args[1], my_env);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		builtin_cd(&args[1], *my_env);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		builtin_exit(&args[1]);
}

void	wait_pipeline(pid_t last_pid)
{
	pid_t	wpid;
	int		status;
	int		exited;

	status = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			exited = WIFEXITED(status);
			if (exited)
				g_exit_status = WEXITSTATUS(status);
			else
				g_exit_status = 1;
		}
		wpid = wait(&status);
	}
}
