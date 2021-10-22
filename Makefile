# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:11:02 by mkamei            #+#    #+#              #
#    Updated: 2021/10/22 11:58:57 by mkamei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR	:= ./srcs
SRCSNAME:=	main.c read_map.c draw_map.c rotate.c handler.c merge_sort.c \
			utils/get_next_line.c utils/utils.c
SRCS	:= $(addprefix $(SRCSDIR)/, $(SRCSNAME))

OBJSDIR :=	./objs
OBJSNAME:=	$(SRCSNAME:.c=.o)
OBJS    :=	$(addprefix $(OBJSDIR)/, $(OBJSNAME))

INCLUDE :=	-I./includes/
NAME	:=	fdf

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
RM		:=	rm -rf

LIBFTDIR	:=	./libft
LIBFT		:=	$(LIBFTDIR)/libft.a
LIBFTTARGET	:=	all

LIBMLXDIR	:=	./minilibx-linux
ifeq ($(shell uname),Linux)
	LIBMLX	:= $(LIBMLXDIR)/libmlx_Linux.a
else
	LIBMLX	:=	$(LIBMLXDIR)/libmlx_Darwin.a
endif

LIBINCLUDE	:= -I./libft -I./minilibx-linux
LIBDIR		:= -L${LIBFTDIR} -L${LIBMLXDIR}
LIBLINK		:= -lft -lXext -lX11
ifeq ($(shell uname),Linux)
	LIBLINK 	+= -lmlx_Linux -lm
else
	LIBLINK		+=	-lmlx_Darwin
	LIBINCLUDE	+=	-I/usr/local/include
endif
LIB			:= $(LIBINCLUDE) $(LIBDIR) $(LIBLINK)

all		:	$(NAME)

$(NAME)	:	$(LIBFT) $(LIBMLX) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME)

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDE) -o $@ -c $<

$(LIBFT):
			make $(LIBFTTARGET) -C $(LIBFTDIR)

$(LIBMLX):
			make -C $(LIBMLXDIR)

clean	:
			$(RM) $(OBJS)
			make clean -C $(LIBFTDIR)
			make clean -C $(LIBMLXDIR)

fclean	: 	clean
			$(RM) $(NAME)
			make fclean -C $(LIBFTDIR)

re		:	fclean all

address	:	CC			=	clang
address	:	CFLAGS		+=	-g -fsanitize=address
address	:	LIBFTTARGET	=	address
address	:	re

leak	:	CC			=	clang
leak	:	CFLAGS		+=	-g -fsanitize=leak
leak	:	LIBFTTARGET	=	leak
leak	:	re

.PHONY:	all clean fclean re address leak
