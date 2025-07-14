/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:12:38 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/14 16:01:34 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_token(const char *s)
{
	return (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2)
		|| *s == '>' || *s == '<' || *s == '|');
}

char	*parse_special_token(const char **s)
{
	char	*token;

	if (!ft_strncmp(*s, ">>", 2) || !ft_strncmp(*s, "<<", 2))
	{
		token = ft_substr(*s, 0, 2);
		*s += 2;
	}
	else
	{
		token = ft_substr(*s, 0, 1);
		(*s)++;
	}
	return (token);
}

// SIMPLEMENTE TESTEO DEL PARSER DE REDIRECCIONES
/* void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		printf("token[%d]: \"%s\"\n", i, tokens[i]);
		i++;
	}
} */

int	process_token(char **tokens, int *i, t_cmd *cmd, t_list **args)
{
	t_redir	*redir;

	if (is_redirection_token(tokens[*i]))
	{
		redir = create_redirection(tokens, i);
		if (!redir)
			return (0);
		add_redir_to_list(&cmd->redirs, redir);
	}
	else
		ft_lstadd_back(args, ft_lstnew(ft_strdup(tokens[*i])));
	return (1);
}

void	handle_heredoc_signal(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
	rl_replace_line("", 0);
	rl_done = 1;
}
