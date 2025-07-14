/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:45:01 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/14 23:01:11 by albcamac         ###   ########.fr       */
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

static int	should_expand_heredoc(char *delimiter, char **cl_del)
{
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{
		*cl_del = remove_quotes(delimiter);
		return (0);
	}
	*cl_del = ft_strdup(delimiter);
	return (1);
}

static void	child_heredoc(int fd, char *clean_delim,
	int should_expand, char **env)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line || g_exit_status == 130 || !ft_strcmp(line, clean_delim))
			break ;
		if (should_expand)
		{
			expanded = expand_var(line, env);
			write(fd, expanded, ft_strlen(expanded));
			write(fd, "\n", 1);
			free(expanded);
		}
		else
			(write(fd, line, ft_strlen(line)), write(fd, "\n", 1));
		free(line);
	}
	free(line);
	exit(0);
}

static int	handle_heredoc_parent(pid_t pid, int *pipefd, char *clean_delim)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	setup_prompt_signals();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(pipefd[0]);
		g_exit_status = 130;
		free(clean_delim);
		return (1);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	free(clean_delim);
	return (0);
}

int	handle_heredoc(char *delimiter, char **env)
{
	int		pipefd[2];
	int		should_expand;
	char	*clean_delim;
	pid_t	pid;

	g_exit_status = 0;
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
	should_expand = should_expand_heredoc(delimiter, &clean_delim);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	if (pid == 0)
	{
		close(pipefd[0]);
		child_heredoc(pipefd[1], clean_delim, should_expand, env);
	}
	return (handle_heredoc_parent(pid, pipefd, clean_delim));
}
