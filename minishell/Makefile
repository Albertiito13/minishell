# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albcamac <albcamac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 00:04:03 by albcamac          #+#    #+#              #
#    Updated: 2025/06/28 16:24:31 by albcamac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= minishell
SRC 		= minishell.c parse_line.c builtins.c
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
