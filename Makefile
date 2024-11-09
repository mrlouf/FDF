# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	fdf

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		=	includes

LIBFTDIR	=	libft

LIBMLX		= 	MLX42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	srcs/fdf.c				\
				srcs/parser.c			\
				srcs/error.c			\
				srcs/matrix.c			\
				srcs/start.c			\
				srcs/matrix_utils.c		\
				srcs/matrix_utils2.c

HEADER		:=	$(INCLUDES)/fdf.h

MAKE		:=	Makefile

OBJS		=	$(SRC:%.c=%.o)

LIBS		=	$(LIBFTDIR)/libft.a $(LIBMLX)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc

CFLAGS		=	-Werror -Wextra -Wall -pthread -g -fsanitize=address#-lglfw

INCLUDE		=	-Iincludes

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c $(HEADER) $(MAKE)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS) $(MAKE) includes/fdf.h
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -lm -ldl -Ofast $(LIBS) -o $(NAME)

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
