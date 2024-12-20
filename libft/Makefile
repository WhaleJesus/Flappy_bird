# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 16:45:37 by sklaps            #+#    #+#              #
#    Updated: 2024/06/03 16:56:45 by sklaps           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SOURCES = \
		ft_atoi.c \
		ft_isprint.c \
		ft_putstr_fd.c \
		ft_strlen.c \
		ft_tolower.c \
		ft_isdigit.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_isalnum.c \
		ft_split.c \
		ft_memcmp.c \
		ft_strrchr.c \
		ft_itoa.c \
		ft_memset.c \
		ft_strmapi.c \
		ft_strlcat.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_calloc.c \
		ft_strncmp.c \
		ft_bzero.c \
		ft_putchar_fd.c \
		ft_putnbr_fd.c \
		ft_memcpy.c \
		ft_strchr.c \
		ft_strnstr.c \
		ft_isascii.c \
		ft_isalpha.c \
		ft_memchr.c \
		ft_putendl_fd.c \
		ft_toupper.c \
		ft_substr.c \
		ft_striteri.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_letters.c \
		ft_numbers.c \
		ft_printf.c \
		get_next_line.c \
		get_next_line_utils.c
BSOURCES = \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c
OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJECTS) $(BOBJECTS)
		   ar -rcs $@ $?

bonus: $(OBJECTS) $(BOBJECTS)
		ar -rcs $(NAME) $?

%.o: %.c
		$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) $(BOBJECTS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
