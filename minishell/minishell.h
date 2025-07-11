/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:45:20 by albcamac          #+#    #+#             */
/*   Updated: 2025/07/11 16:40:09 by albcamac         ###   ########.fr       */
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
# include <sys/stat.h>

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
char			**filter_empty_tokens(char **tokens);
int				has_simple_pipe(char **args);

void			builtin_echo(char **args);
void			builtin_pwd(void);
void			builtin_env(char **envp);
void			builtin_exit(char **args);
void			builtin_cd(char **args, char **envp);
void			builtin_unset(char **args, char ***my_env);
char			**create_default_env(void);
char			**dup_env(char **envp);
char			*get_env_value(char *var, char **my_env);
char			**add_to_env(char **env, char *new_var);
void			builtin_export(char **args, char ***my_env);
int				is_valid_identifier(char *s);

void			execute_external(char **args, char **envp);
void			execute_pipeline(char **segments, char **my_env);
char			*find_executable(char *cmd, char **envp);
void			run_cmd_in_child(char *seg, int in_fd, int *fd, char **my_env);
int				is_builtin(char **args);
void			execute_builtin_in_child(char **args, char ***my_env);
void			wait_pipeline(pid_t last_pid);
void			print_sorted_env(char **env);
void			increment_shlvl(char ***my_env);
void			handle_export_arg(char *arg, char ***my_env);

//signals
void			handle_sigint(int sig);
void			handle_sigquit(int sig);
void			check_child_signal(int status);
void			setup_prompt_signals(void);
void			setup_exec_signals(void);

//redirections
int				handle_heredoc(char *delimiter, char **my_env);
int				apply_redirections(t_redir *redirs, char **my_env);
void			free_cmd(t_cmd *cmd);

//redirections utils
int				redir_input(char *file);
int				redir_output(char *file);
int				redir_append(char *file);
int				redir_heredoc(char *delimiter, char **my_env);

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
