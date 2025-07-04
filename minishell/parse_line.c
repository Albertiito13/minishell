/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:58:54 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 02:57:47 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_quoted(const char **s, char quote)
{
	const char	*start;
	char		*content;

	(*s)++;
	start = *s;
	while (**s && **s != quote)
		(*s)++;
	content = ft_substr(start, 0, *s - start);
	if (**s == quote)
		(*s)++;
	return (content);
}

static char	*parse_token(const char **s)
{
	char		*token;
	char		*part;
	const char	*start;

	token = ft_calloc(1, 1);
	while (**s && **s != ' ' && **s != '\t')
	{
		if (**s == '\'' || **s == '"')
			part = parse_quoted(s, **s - 0);
		else
		{
			start = *s;
			while (**s && **s != ' ' && **s != '\t'
				&& **s != '\'' && **s != '"')
				(*s)++;
			part = ft_substr(start, 0, *s - start);
		}
		token = ft_strjoin_free(token, part);
		free(part);
	}
	return (token);
}

char	**parse_line(const char *s)
{
	char	**tokens;
	int		i;

	tokens = malloc(sizeof(char *) * (ft_strlen(s) + 2));
	if (!tokens)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s)
		{
			tokens[i] = parse_token(&s);
			i++;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
		free(split[i++]);
	free(split);
}
