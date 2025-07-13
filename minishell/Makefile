# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alegarci <alegarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/11 00:04:03 by albcamac          #+#    #+#              #
#    Updated: 2025/07/13 12:46:14 by alegarci         ###   ########.fr        #
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
				signals/signal_utils.c \
				redirections/tokens.c \
				redirections/parse_redirections.c \
				redirections/redirections.c \
				redirections/redirections_utils.c \
				redirections/heredoc_utils.c \
				env_default.c
				
OBJ 		= $(SRC:.c=.o)
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
LIBFT_DIR	= libft

LIBFT	= $(LIBFT_DIR)/libft.a
LIBS = -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) $(LIBS) -lft
	@echo "\033[1;36m"
	@echo "  __  __ _       _     _          _ _ "
	@echo " |  \/  (_)     (_)   | |        | | |"
	@echo " | \\  / |_ _ __  _ ___| |__   ___| | |"
	@echo " | |\/| | | '_ \\| / __| '_ \\ / _ \\ | |"
	@echo " | |  | | | | | | \\__ \\ | | |  __/ | |"
	@echo " |_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|"
	@echo ""
	@echo "    Proyecto de albcamac y alegarci"
	@echo "\033[0m"
	@echo "   Minishell compiled successfully!"
	@echo ""

clean:
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean >/dev/null

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean >/dev/null

re: fclean all

.PHONY: all clean fclean re
