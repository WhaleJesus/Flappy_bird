# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdaems <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 14:48:15 by fdaems            #+#    #+#              #
#    Updated: 2024/12/20 04:22:40 by sklaps           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = flap
CC = cc
FLAGS = -g
SRC_DIR = srcs
OBJS_DIR = objs
INC_DIR = includes

SRCS = $(SRC_DIR)/flappybird.c \
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

MINILIBX = mlx
LIBFT = includes/libft

FMS = -L$(LIBFT) -lft -L$(MINILIBX) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

all: compilemake $(NAME)

compilemake:
		make -C $(MINILIBX)
		make -C $(LIBFT)
		mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^ $(FMS)

clean:
	rm -r $(OBJS_DIR)
	make clean -C $(MINILIBX)
	make fclean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all compilemake clean fclean re
