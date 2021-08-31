SRC_DIR := ./srcs/
SRCNAME	:=	fdf.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCNAME))
OBJS	:= $(SRCS:.c=.o)
INCLUDE := -I./includes/
NAME	:= fdf

CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror
RM		:= rm -rf

LIBFTDIR		:= ./libft
LIBFTNAME 		:= ft
LIBFTINCLUDEDIR := $(LIBFTDIR)
LIBFT			:= $(LIBFTDIR)/libft.a
LIBFTTARGET		:= all

UNAME 	:= $(shell uname)
ifeq ($(UNAME),Linux)
	LIBMLXDIR		:= ./minilibx_linux
	LIBMLX			:= $(LIBMLXDIR)/libmlx.dylib
else
	LIBMLXDIR		:= ./minilibx_macos
	LIBMLX			:= $(LIBMLXDIR)/libmlx.a
endif
LIBMLXNAME			:= mlx
LIBMLXINCLUDEDIR	:= $(LIBMLXDIR)

LIBDIR		:= -L${LIBFTDIR} -L${LIBMLXDIR}
LIBLINK		:= -l${LIBFTNAME} -l${LIBMLXNAME}
LIBINCLUDE	:= -I${LIBFTINCLUDEDIR} -I${LIBMLXINCLUDEDIR}

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(LIBFT) $(LIBMLX) $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBINCLUDE) $(LIBDIR) $(LIBLINK) -o $(NAME)

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

debug	: CFLAGS += -g
debug	: LIBFTTARGET := debug
debug	: re

address	: CFLAGS += -g -fsanitize=address
address	: LIBFTTARGET := address
address	: re

.PHONY:	all clean fclean re debug address
