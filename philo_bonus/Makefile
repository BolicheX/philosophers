# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/07 12:20:27 by jose-jim          #+#    #+#              #
#    Updated: 2025/09/02 21:20:48 by jose-jim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -rf

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

# The name of the executable
PS_NAME = philo_bonus

# Source files
PS_SOURCE = main_bonus.c \
			aux_bonus.c \
			init_exit_bonus.c \
			philosopher_bonus.c

# Object files
PS_OBJ = $(PS_SOURCE:.c=.o)

all:	$(PS_NAME)

$(PS_NAME): $(PS_OBJ)
	@$(CC) $(CFLAGS) $(PS_OBJ) -o $(PS_NAME)
	@echo "$(BLUE)$(PS_NAME) created!$(DEF_COLOR)"

%.o: %.c philo_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(REMOVE) $(PS_OBJ)
	@echo "$(BLUE)[PHILO_BONUS] Object files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(REMOVE) $(PS_NAME)
	@echo "$(BLUE)[PHILO_BONUS] Executable files and directories cleaned!$(DEF_COLOR)"

re: fclean all