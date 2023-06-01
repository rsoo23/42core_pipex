# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 10:39:28 by rsoo              #+#    #+#              #
#    Updated: 2023/06/01 10:44:49 by rsoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS_DIR = srcs
SRCS_FILES = main
C_FILES = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJ = $(C_FILES:.c=.o)

LIBFT_DIR = libft
LIBFT = libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT)
