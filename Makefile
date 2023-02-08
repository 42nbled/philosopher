# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbled <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 22:36:13 by nbled             #+#    #+#              #
#    Updated: 2022/12/12 22:36:14 by nbled            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

SRCS =	main.c \
		philo_parsing.c \
		philo_th.c \
		philo_utils.c \
		philo_free.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -pthread


all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re