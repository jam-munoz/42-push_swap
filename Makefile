# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/15 17:54:04 by joamunoz          #+#    #+#              #
#    Updated: 2026/10/25 07:49:56 by joamunoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
BONUS_NAME = checker
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -g

SOURCE_FILES := $(filter-out b_checker_%.c,$(wildcard *.c)) \
	$(wildcard operations/*.c) $(wildcard ft_printf/*.c)

BONUS_SOURCE_FILES := $(wildcard b_*.c)

OBJECTS = ${SOURCE_FILES:.c=.o}

%.o: %.c d_push_swap.h o_operations.h ft_printf.h b_checker_bonus.h
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJECTS}
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

all: ${NAME}

bonus: ${BONUS_SOURCE_FILES}
		$(CC) $(CFLAGS) $(BONUS_SOURCE_FILES) -o $(BONUS_NAME)

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
