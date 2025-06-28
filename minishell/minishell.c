/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:47:42 by albcamac          #+#    #+#             */
/*   Updated: 2025/06/28 16:23:56 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
	char	**args;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		args = parse_line(line);
		if (args && args[0])
		{
			if (ft_strncmp(args[0], "echo", 5) == 0)
				builtin_echo(&args[1]);
		}
		free_split(args);
		free(line);
	}
	return (0);
}
