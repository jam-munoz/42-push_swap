# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/15 17:54:04 by joamunoz          #+#    #+#              #
#    Updated: 2026/10/02 09:10:03 by joamunoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -g

SOURCE_FILES := $(wildcard *.c) $(wildcard ft_printf/*.c)

OBJECTS = ${SOURCE_FILES:.c=.o}

%.o: %.c push_swap.h ./ft_printf/ft_printf.h
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

all: ${NAME}

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
