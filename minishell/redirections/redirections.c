/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:00:02 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/13 15:53:20 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_input_redir(t_redir *r)
{
	return (redir_input(r->file));
}

static int	handle_output_redir(t_redir *r)
{
	return (redir_output(r->file));
}

static int	handle_append_redir(t_redir *r)
{
	return (redir_append(r->file));
}

static int	handle_heredoc_redir(t_redir *r, char **env)
{
	if (redir_heredoc(r->file, env))
		return (1);
	if (g_exit_status == 130)
		return (1);
	return (0);
}

int	apply_redirections(t_redir *r, char **env)
{
	while (r)
	{
		if (r->type == REDIR_IN && handle_input_redir(r))
			return (1);
		else if (r->type == REDIR_OUT && handle_output_redir(r))
			return (1);
		else if (r->type == REDIR_APPEND && handle_append_redir(r))
			return (1);
		else if (r->type == REDIR_HEREDOC && handle_heredoc_redir(r, env))
			return (1);
		r = r->next;
	}
	return (0);
}
