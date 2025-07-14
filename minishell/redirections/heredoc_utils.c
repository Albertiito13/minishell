/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:45:01 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/14 16:02:09 by albcamac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*remove_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2
		&& ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

static int	should_expand_heredoc(char *delimiter, char **clean_delim)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{
		*clean_delim = remove_quotes(delimiter);
		return (0);
	}
	*clean_delim = ft_strdup(delimiter);
	return (1);
}

static void	write_heredoc_line(char *line,
	int should_expand, int fd, char **my_env)
{
	char	*tmp;

	if (should_expand)
	{
		tmp = expand_var(line, my_env);
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(tmp);
	}
	else
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

static void	process_heredoc_input(int fd, char *clean_delim,
	int should_expand, char **my_env)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || g_exit_status == 130 || !ft_strcmp(line, clean_delim))
			break ;
		write_heredoc_line(line, should_expand, fd, my_env);
		free(line);
	}
	free(line);
}

int	handle_heredoc(char *delimiter, char **my_env)
{
	int		pipefd[2];
	int		should_expand;
	char	*clean_delim;

	g_exit_status = 0;
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
	should_expand = should_expand_heredoc(delimiter, &clean_delim);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	process_heredoc_input(pipefd[1], clean_delim, should_expand, my_env);
	free(clean_delim);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	return (0);
}
