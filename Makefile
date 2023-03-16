# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamasson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 17:51:16 by lamasson          #+#    #+#              #
#    Updated: 2023/03/16 17:36:55 by lamasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC	= clang

CFLAGS	= -Wall -Wextra -Werror -g3

RM	= rm -rf

NAME	= pipex

SRCS	= main.c \
	  ft_get_path.c \
	  ft_pipe.c \
	  ft_exec.c

SRCS_BONUS = main_bonus.c \
	     ft_get_path_bonus.c \
	     ft_pipe_bonus.c \
	     ft_here_doc_bonus.c \
	     ft_exec_bonus.c

OBJS	= ${SRCS:%.c=%.o}

OBJS_BONUS = ${SRCS_BONUS:%.c=%.o}

LIBFT	= ./libft

LIB	= ./libft/libft.a

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
	@make -C ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

all:	${NAME}

bonus:	${OBJS_BONUS}
	@make -C ${LIBFT}
	@${CC} ${CFLAGS} ${OBJS_BONUS} ${LIB} -o ${NAME}

clean:
	@make -C ${LIBFT} clean
	@${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	@make -C ${LIBFT} fclean
	@${RM} ${NAME}

re:	fclean all

.PHONY: all clean fclean bonus re
