/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:45:20 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/04 19:57:46 by alegarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

extern int	g_exit_status;

char	**parse_line(const char *s);
void	free_split(char **split);
char	*ft_strjoin_free(char *s1, char *s2);
char	*expand_var(char *input, char **my_env);

void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_env(char **envp);
void	builtin_exit(char **args);
void	builtin_cd(char **args, char **envp);
void	builtin_unset(char **args, char ***my_env);
char	**dup_env(char **envp);
char	*get_env_value(char *var, char **my_env);
char	**add_to_env(char **env, char *new_var);
void	builtin_export(char **args, char ***my_env);

void	execute_external(char **args, char **envp);
void	execute_pipeline(char **segments, char **my_env);
char	*find_executable(char *cmd, char **envp);

//signals
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_prompt_signals(void);
void	check_child_signal(int status);

#endif
