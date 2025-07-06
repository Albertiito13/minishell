/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:19:17 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/06 17:19:40 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**list_to_str_array(t_list *list)
{
	char	**array;
	int		i;
	t_list	*tmp;

	array = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = list;
	while (tmp)
	{
		array[i++] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
