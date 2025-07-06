/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:01:50 by alegarci          #+#    #+#             */
/*   Updated: 2025/07/06 17:15:52 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int redir_input(char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), perror("dup2"), 1);
	close(fd);
	return (0);
}

int redir_output(char *file)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), perror("dup2"), 1);
	close(fd);
	return (0);
}

int redir_append(char *file)
{
	int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(file), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), perror("dup2"), 1);
	close(fd);
	return (0);
}

int redir_heredoc(char *delimiter)
{
	return (handle_heredoc(delimiter));
}
