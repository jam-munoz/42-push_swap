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

COMMON_SOURCE_FILES = \
	a_chunk.c \
	a_disorder.c \
	a_flags.c \
	a_insertion.c \
	a_radix.c \
	a_sort.c \
	a_strategy.c \
	d_index.c \
	d_parser.c \
	d_utils.c \
	ft_printf.c \
	ft_printf_dec.c \
	ft_printf_float.c \
	ft_printf_hex.c \
	m_benchmark.c \
	m_benchmark_state.c \
	o_push.c \
	o_rev_rotate.c \
	o_rotate.c \
	o_swap.c

SOURCE_FILES = \
	d_main.c \
	$(COMMON_SOURCE_FILES)

BONUS_SOURCE_FILES = \
	b_checker_bonus.c \
	b_checker_output_bonus.c \
	ft_get_next_line.c \
	ft_get_next_line_utils.c \
	$(COMMON_SOURCE_FILES)

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
