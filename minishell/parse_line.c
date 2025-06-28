/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:58:54 by albcamac          #+#    #+#             */
/*   Updated: 2025/06/28 16:16:02 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(const char *s)
{
	int		count;
	char	quote;

	count = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
		{
			count++;
			if (*s == '\'' || *s == '"')
			{
				quote = *s++;
				while (*s && *s != quote)
					s++;
				if (*s)
					s++;
			}
			else
			{
				while (*s && *s != ' ' && *s != '\t'
					&& *s != '\'' && *s != '"')
					s++;
			}
		}
	}
	return (count);
}

char	**parse_line(const char *s)
{
	char		**tokens;
	const char	*start;
	size_t		len;
	int			i;
	char		quote;

	i = 0;
	if (!s)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!tokens)
		return (NULL);
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (!*s)
			break ;
		if (*s == '\'' || *s == '"')
		{
			quote = *s++;
			start = s;
			while (*s && *s != quote)
				s++;
			len = s - start;
			tokens[i++] = ft_substr(start, 0, len);
			if (*s == quote)
				s++;
		}
		else
		{
			start = s;
			while (*s && *s != ' ' && *s != '\t'
				&& *s != '\'' && *s != '"')
				s++;
			len = s - start;
			tokens[i++] = ft_substr(start, 0, len);
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

void	free_split(char **split)
{
	int i = 0;
	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}
