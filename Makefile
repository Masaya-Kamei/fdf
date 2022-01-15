# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:11:02 by mkamei            #+#    #+#              #
#    Updated: 2022/01/15 15:42:16 by mkamei           ###   ########.fr        #
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

BONUS_SRCSDIR	:= $(addprefix ./bonus/, $(SRCSDIR))
BONUS_SRCSNAME	:= $(subst .c,_bonus.c,$(SRCSNAME))
BONUS_SRCS		:= $(addprefix $(BONUS_SRCSDIR)/, $(BONUS_SRCSNAME))

BONUS_OBJSDIR	:=	$(addprefix ./bonus/, $(OBJSDIR))
BONUS_OBJSNAME	:=	$(BONUS_SRCSNAME:.c=.o)
BONUS_OBJS		:=	$(addprefix $(BONUS_OBJSDIR)/, $(BONUS_OBJSNAME))

BONUS_INCLUDE	:=	$(subst includes,bonus/includes,$(INCLUDE))
BONUS_NAME		:=	$(addprefix ./bonus/, $(NAME))

CC		:=	gcc
CFLAGS	:=	-Wall -Wextra -Werror
RM		:=	rm -rf

LIBFTDIR	:=	./libft
LIBFT		:=	$(LIBFTDIR)/libft.a
LIBFTTARGET	:=	all

ifeq ($(shell uname),Linux)
	LIBMLXDIR	:=	./minilibx-linux
	LIBMLX		:= $(LIBMLXDIR)/libmlx_Linux.a
else
	LIBMLXDIR	:=	./minilibx_macos
	LIBMLX		:=	$(LIBMLXDIR)/libmlx.a
endif

LIBINCLUDE	:=	-I${LIBFTDIR} -I${LIBMLXDIR}
LIBDIR		:=	-L${LIBFTDIR} -L${LIBMLXDIR}
LIBLINK		:=	-lft
ifeq ($(shell uname),Linux)
	LIBLINK 	+=	-lmlx_Linux -lm -lXext -lX11
else
	LIBLINK		+=	-lmlx -framework OpenGL -framework AppKit
endif
LIB			:=	$(LIBINCLUDE) $(LIBDIR) $(LIBLINK)


all		:	$(NAME)

$(NAME)	:	$(LIBFT) $(LIBMLX) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIB) -o $(NAME)

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDE) -o $@ -c $<

bonus			:	$(BONUS_NAME)

$(BONUS_NAME)	:	$(LIBFT) $(LIBMLX) $(BONUS_OBJS)
			$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(BONUS_OBJS) $(LIB) -o $(BONUS_NAME)

$(BONUS_OBJSDIR)/%.o	:	$(BONUS_SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(LIBINCLUDE) -o $@ -c $<

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

.PHONY:	all clean fclean re bonus address leak
