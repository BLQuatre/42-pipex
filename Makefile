# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 10:30:46 by cauvray           #+#    #+#              #
#    Updated: 2024/11/26 20:49:10 by cauvray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT_FILE	= libft.a
LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILE))

# Files for compilation
CORE_FILES		= pipex.c utils.c errors.c cmds.c
DEBUG_FILES		= debug.c

ALL_FILES		= $(CORE_FILES) $(DEBUG_FILES)

SRCS_DIR	= srcs
OBJS_DIR	= objs
OBJS_FILES	= $(ALL_FILES:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

INC_DIR		= includes
INC_FLAGS	= -I./$(INC_DIR)

GREEN	= \033[0;32m
CYAN	= \033[0;36m
RESET	= \033[0m

SUCCESS	= $(GREEN)[SUCCESS]$(RESET)
INFO	= $(CYAN)[INFO]$(RESET)

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/**/%.c | $(OBJS_DIR)
	@echo "$(INFO) Compiling $<..."
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

lib:
	@if [ -d "./$(LIBFT_DIR)" ]; then \
		echo "$(INFO) Updating $(LIBFT_DIR) with git pull..."; \
		cd $(LIBFT_DIR) && git pull; \
	else \
		echo "$(INFO) Cloning $(LIBFT_DIR)..."; \
		git clone https://github.com/BLQuatre/42-my_libft.git $(LIBFT_DIR); \
	fi
	@echo "$(INFO) Compiling $(LIBFT_DIR)..."
	@make -C $(LIBFT_DIR)
	@echo "$(SUCCESS) $(LIBFT_DIR) compiled."


$(NAME): lib $(OBJS)
	@echo "$(INFO) Compiling $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "$(SUCCESS) $(NAME) compiled."

clean:
	@echo "$(INFO) Removing $(LIBFT_DIR)...";
	rm -rf $(LIBFT_DIR);
	@echo "$(INFO) Removing $(OBJS_DIR)...";
	rm -rf $(OBJS_DIR);
	@echo "$(SUCCESS) Objects and libs removed."

fclean: clean
	@echo "$(INFO) Removing $(NAME)..."
	rm -f $(NAME)
	@echo "$(SUCCESS) $(NAME) removed."

re: fclean all

.PHONY: all lib clean fclean re
