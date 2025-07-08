/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 01:38:37 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/08 21:43:08 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_char(char *str, char c)
{
	char	tmp[2];
	char	*new;

	tmp[0] = c;
	tmp[1] = '\0';
	new = ft_strjoin_free(str, tmp);
	return (new);
}

static char	*handle_dollar(char *input, int *i, char **my_env)
{
	char	*var;
	char	*val;
	int		start;

	if (input[*i] == '?')
	{
		(*i)++;
		val = ft_itoa(g_exit_status);
		return (val);
	}
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
	{
		start = *i;
		while (ft_isalnum(input[*i]) || input[*i] == '_')
			(*i)++;
		var = ft_substr(input, start, *i - start);
		val = get_env_value(var, my_env);
		free(var);
		if (val)
			return (ft_strdup(val));
		else
			return (ft_calloc(1, 1));
	}
	return (ft_strdup("$"));
}

static void	update_quote(char c, char *quote)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote && c == *quote)
		*quote = 0;
}

char	*expand_var(char *input, char **my_env)
{
	int		i;
	char	*result;
	char	*exp;
	char	quote;

	i = 0;
	result = ft_calloc(1, 1);
	quote = 0;
	while (input[i])
	{
		update_quote(input[i], &quote);
		if (input[i] == '$' && quote != '\'')
		{
			i++;
			exp = handle_dollar(input, &i, my_env);
			result = ft_strjoin_free(result, exp);
			free(exp);
		}
		else
		{
			result = append_char(result, input[i]);
			i++;
		}
	}
	return (result);
}
