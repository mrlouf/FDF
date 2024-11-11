# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	fdf

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	includes

LIBFTDIR	:=	libft

URLMLX		:=	https://github.com/42-Madrid-Fundacion-Telefonica/MLX42.git

MLXDIR		:= 	MLX42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			:=	srcs/fdf.c				\
				srcs/parser.c			\
				srcs/error.c			\
				srcs/matrix.c			\
				srcs/start.c			\
				srcs/matrix_utils.c		\
				srcs/drawing_utils.c	\
				srcs/hooks.c

MLX_FLAG	:=	.mlx_flag

HEADER		:=	$(INCLUDES)/fdf.h

MAKE		:=	Makefile

OBJS		:=	$(SRC:%.c=%.o)

LIBS		:=	$(LIBFTDIR)/libft.a $(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	-cc

CFLAGS		:=	-Werror -Wextra -Wall -g -fsanitize=address#-lglfw

INCLUDE		:=	-Iincludes

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS) Makefile includes/fdf.h
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBS) -o $(NAME)

make_libft:
	make -C libft

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft
	rm -fr MLX42/build

re: fclean all

.PHONY:  all clean fclean re make_libft
