/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:00:02 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/06 17:30:07 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break;
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}

int	apply_redirections(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->type == REDIR_IN)
		{
			if (redir_input(redirs->file))
				return (1);
		}
		else if (redirs->type == REDIR_OUT)
		{
			if (redir_output(redirs->file))
				return (1);
		}
		else if (redirs->type == REDIR_APPEND)
		{
			if (redir_append(redirs->file))
				return (1);
		}
		else if (redirs->type == REDIR_HEREDOC)
		{
			if (redir_heredoc(redirs->file))
				return (1);
		}
		redirs = redirs->next;
	}
	return (0);
}

void	free_cmd(t_cmd *cmd)
{
	t_redir *tmp;

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



