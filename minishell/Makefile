# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 00:04:03 by albcamac          #+#    #+#              #
#    Updated: 2025/07/08 22:18:47 by albcamac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC 		= minishell.c \
				builtins/built_export.c \
				builtins/built_export_utils.c \
				builtins/built_unset.c \
				builtins/built_echo.c \
				builtins/built_exit.c \
				builtins/built_env.c \
				builtins/built_pwd.c \
				builtins/built_cd.c \
				execute.c \
				execute_pipeline.c \
				execute_pipeline_utils.c \
				expand_var.c \
				parse_line.c \
				env_utils.c \
				signals/signals.c \
				redirections/tokens.c \
				redirections/parse_redirections.c \
				redirections/redirections.c \
				redirections/redirections_utils.c \

OBJ 		= $(SRC:.c=.o)
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
LIBFT_DIR	= libft

LIBFT	= $(LIBFT_DIR)/libft.a
LIBS = -lreadline
all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) $(LIBS) -lft

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean >/dev/null

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null

re: fclean all

.PHONY: all clean fclean re
