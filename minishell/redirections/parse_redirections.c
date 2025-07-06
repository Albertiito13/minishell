/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:34:38 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/06 17:15:39 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection_token(const char *token)
{
	return (!ft_strcmp(token, "<") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"));
}

t_redir_type	get_redir_type(const char *token)
{
	if (!ft_strcmp(token, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(token, ">"))
		return (REDIR_OUT);
	if (!ft_strcmp(token, ">>"))
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

t_redir	*create_redirection(char **tokens, int *i)
{
	t_redir	*redir;

	if (!tokens[*i + 1])
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = get_redir_type(tokens[*i]);
	*i += 1;
	redir->file = ft_strdup(tokens[*i]);
	redir->next = NULL;
	return (redir);
}

void	add_redir_to_list(t_redir **list, t_redir *new_redir)
{
	t_redir	*temp;

	if (!*list)
		*list = new_redir;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

t_cmd	*parse_command(char **tokens)
{
	t_cmd	*cmd;
	t_list	*args_list;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->redirs = NULL;
	args_list = NULL;
	i = 0;
	while (tokens[i])
	{
		if (!process_token(tokens, &i, cmd, &args_list))
			return (NULL);
		i++;
	}
	cmd->argv = list_to_str_array(args_list);
	ft_lstclear(&args_list, free);
	return (cmd);
}
