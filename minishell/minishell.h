/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:45:20 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/06 20:19:15 by alegarci         ###   ########.fr       */
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

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redirs;
}	t_cmd;

char			**parse_line(const char *s);
void			free_split(char **split);
char			*ft_strjoin_free(char *s1, char *s2);
char			*expand_var(char *input, char **my_env);

void			builtin_echo(char **args);
void			builtin_pwd(void);
void			builtin_env(char **envp);
void			builtin_exit(char **args);
void			builtin_cd(char **args, char **envp);
void			builtin_unset(char **args, char ***my_env);
char			**dup_env(char **envp);
char			*get_env_value(char *var, char **my_env);
char			**add_to_env(char **env, char *new_var);
void			builtin_export(char **args, char ***my_env);

void			execute_external(char **args, char **envp);
void			execute_pipeline(char **segments, char **my_env);
char			*find_executable(char *cmd, char **envp);
void			run_command_in_child(char *segment, int in_fd, int *fd, char **my_env);


//signals
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			check_child_signal(int status);
void			setup_prompt_signals(void);
void 			setup_exec_signals(void);

//redirections
int				handle_heredoc(char *delimiter);
int				apply_redirections(t_redir *redirs);
void			free_cmd(t_cmd *cmd);

//redirections utils
int				redir_input(char *file);
int				redir_output(char *file);
int				redir_append(char *file);
int				redir_heredoc(char *delimiter);

//parse redirections
int				is_redirection_token(const char *token);
t_redir_type	get_redir_type(const char *token);
t_redir			*create_redirection(char **tokens, int *i);
void			add_redir_to_list(t_redir **list, t_redir *new_redir);
t_cmd			*parse_command(char **tokens);

//tokens
int				is_special_token(const char *s);
int				process_token(char **tokens, int *i, t_cmd *cmd, t_list **args);
char			*parse_special_token(const char **s);

#endif
