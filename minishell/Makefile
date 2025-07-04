# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 00:04:03 by albcamac          #+#    #+#              #
#    Updated: 2025/07/04 01:39:19 by albcamac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC 		= minishell.c parse_line.c builtins.c env_utils.c signals/signals.c \
				execute.c execute_pipeline.c expand_var.c
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
