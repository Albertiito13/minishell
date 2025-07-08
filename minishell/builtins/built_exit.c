/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:06:11 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/08 17:06:38 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (args[0][i] != '\0')
		{
			(ft_putstr_fd("exit: ", 2), ft_putstr_fd(args[0], 2));
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
