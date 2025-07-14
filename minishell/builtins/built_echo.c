/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:04:27 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/14 22:55:22 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	i = 0;
	newline = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != 0)
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		(ft_printf("%s", args[i]), g_exit_status = 0);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (newline)
		(ft_printf("\n"), g_exit_status = 0);
}
