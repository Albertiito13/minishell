/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:45:20 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/02 23:22:10 by albcamac         ###   ########.fr       */
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

extern int g_exit_status;

char	**parse_line(const char *s);
void	free_split(char **split);

void	builtin_echo(char **args);
void	builtin_pwd(void);
void	builtin_env(char **envp);
void	builtin_exit(char **args);
void	builtin_cd(char **args, char **envp);
void	builtin_unset(char **args, char ***my_env);
char	**dup_env(char **envp);



#endif
