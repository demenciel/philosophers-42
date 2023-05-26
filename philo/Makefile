# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouture <acouture@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 15:51:56 by acouture          #+#    #+#              #
#    Updated: 2023/05/26 15:38:29 by acouture         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CFLAGS  := -pthread -Wextra -Wall -Werror
# LDFLAGS := -fsanitize=thread

SRC_PATH = src/
OBJ_PATH = obj/

HEADERS	:= -I ./include
SRC		:= main.c \
			utils.c \
			thread.c \
			actions.c \
			init.c \
			checkers.c


SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

all: $(NAME)
	@exec 2>/dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) 

$(NAME): $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@printf "$(GREEN)philo compiling: done$(RESET)\n"

debug: $(NAME)
	@$(CC) -g $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)philo clean: done$(RESET)\n"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
