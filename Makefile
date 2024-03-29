# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:11:02 by mkamei            #+#    #+#              #
#    Updated: 2022/02/10 13:15:34 by mkamei           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCSDIR	:= srcs
SRCSNAME:=	main.c read_map.c draw_map.c \
			handler/handler.c handler/map_ope.c \
			utils/merge_sort.c utils/get_next_line.c utils/exit.c utils/matrix.c
SRCS	:= $(addprefix $(SRCSDIR)/, $(SRCSNAME))

OBJSDIR :=	objs
OBJSNAME:=	$(SRCSNAME:.c=.o)
OBJS    :=	$(addprefix $(OBJSDIR)/, $(OBJSNAME))

INCLUDE :=	-I./includes/
NAME	:=	fdf

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
RM		:=	rm -rf

LIBDIR		:= lib

LIBFTDIR	:=	$(LIBDIR)/libft
LIBFT		:=	$(LIBFTDIR)/libft.a
LIBFTTARGET	:=	all

ifeq ($(shell uname),Linux)
	LIBMLXDIR	:=	$(LIBDIR)/minilibx-linux
	LIBMLX		:= $(LIBMLXDIR)/libmlx_Linux.a
else
	LIBMLXDIR	:=	$(LIBDIR)/minilibx_macos
	LIBMLX		:=	$(LIBMLXDIR)/libmlx.a
endif

LIBINCLUDE	:=	-I${LIBFTDIR} -I${LIBMLXDIR}
LIBPATH		:=	-L${LIBFTDIR} -L${LIBMLXDIR}
LIBLINK		:=	-lft
ifeq ($(shell uname),Linux)
	LIBLINK 	+=	-lmlx_Linux -lm -lXext -lX11
else
	LIBLINK		+=	-lmlx -framework OpenGL -framework AppKit
endif
LIB			:=	$(LIBINCLUDE) $(LIBPATH) $(LIBLINK)


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
			$(RM) $(OBJS) $(BONUS_OBJS)
			make clean -C $(LIBFTDIR)
			make clean -C $(LIBMLXDIR)

fclean	: 	clean
			$(RM) $(NAME) $(BONUS_NAME)
			make fclean -C $(LIBFTDIR)

re		:	fclean all

address	:	CFLAGS		+=	-g -fsanitize=address
address	:	LIBFTTARGET	=	address
address	:	re

leak	:	CC			=	/usr/local/opt/llvm/bin/clang
leak	:	CFLAGS		+=	-g -fsanitize=leak
leak	:	LIBFTTARGET	=	leak
leak	:	re

.PHONY:	all clean fclean re address leak
