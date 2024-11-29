# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 10:30:46 by cauvray           #+#    #+#              #
#    Updated: 2024/11/29 06:50:34 by cauvray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT_FILE	= libft.a
LIBFT_LIB	= $(addprefix $(LIBFT_DIR)/, $(LIBFT_FILE))

CORE_FILES	= pipex.c utils.c errors.c

ALL_FILES	= $(CORE_FILES)

SRCS_DIR	= srcs
OBJS_DIR	= objs
OBJS_FILES	= $(ALL_FILES:.c=.o)
OBJS		= $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

INC_DIR		= includes
INC_FLAGS	= -I $(INC_DIR)

GREEN	= \033[0;32m
CYAN	= \033[0;36m
RESET	= \033[0m
GRAY	= \033[90m

SUCCESS	= $(GREEN)[SUCCESS]$(RESET)
INFO	= $(CYAN)[INFO]$(RESET)

all: $(NAME)

$(OBJS_DIR):
	@if [ ! -d ./$(OBJS_DIR) ]; then \
		echo "$(INFO) Creating $(OBJS_DIR) directory..."; \
		echo "$(GRAY)mkdir -p $(OBJS_DIR)"; \
		mkdir -p $(OBJS_DIR); \
	fi

$(OBJS_DIR)/%.o: $(SRCS_DIR)/*/%.c | $(OBJS_DIR)
	@echo "$(INFO) Compiling $<...$(GRAY)"
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

lib:
	@if [ -d "./$(LIBFT_DIR)" ]; then \
		echo "$(INFO) Updating $(LIBFT_DIR) with git pull...$(GRAY)"; \
		echo "$(GRAY)cd $(LIBFT_DIR) && git pull"; \
		cd $(LIBFT_DIR) && git pull; \
	else \
		echo "$(INFO) Cloning $(LIBFT_DIR)...$(GRAY)"; \
		echo "$(GRAY)git clone https://github.com/BLQuatre/42-my_libft.git $(LIBFT_DIR)"; \
		git clone https://github.com/BLQuatre/42-my_libft.git $(LIBFT_DIR); \
	fi
	@echo "$(INFO) Compiling $(LIBFT_DIR)...$(GRAY)"
	@make -C $(LIBFT_DIR)
	@echo "$(SUCCESS) $(LIBFT_DIR) compiled."


$(NAME): lib $(OBJS)
	@echo "$(INFO) Compiling $(NAME)...$(GRAY)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "$(SUCCESS) $(NAME) compiled."

clean:
	@echo "$(INFO) Removing $(LIBFT_DIR)...$(GRAY)";
	rm -rf $(LIBFT_DIR);
	@echo "$(INFO) Removing $(OBJS_DIR)...$(GRAY)";
	rm -rf $(OBJS_DIR);
	@echo "$(SUCCESS) Objects and libs removed."

fclean: clean
	@echo "$(INFO) Removing $(NAME)...$(GRAY)"
	rm -f $(NAME)
	@echo "$(SUCCESS) $(NAME) removed."

re: fclean all

.PHONY: all lib clean fclean re
