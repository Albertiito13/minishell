/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:12:38 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/13 15:52:38 by alegarci         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (!cmd)
		return ;
	if (cmd->argv)
		free_split(cmd->argv);
	while (cmd->redirs)
	{
		tmp = cmd->redirs->next;
		free(cmd->redirs->file);
		free(cmd->redirs);
		cmd->redirs = tmp;
	}
	free(cmd);
}