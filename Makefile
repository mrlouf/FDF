# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	fdf

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		=	includes

LIBFTDIR	=	libft

LIBMLX		= 	MLX42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	srcs/fdf.c				\
				srcs/parser.c			\
				srcs/error.c

HEADER		=	$(INCLUDES)/fdf.h

MAKE		=	Makefile

OBJS		=	$(SRC:%.c=%.o)

LIBS		=	$(LIBFTDIR)/libft.a $(LIBMLX)/build/libmlx42.a 

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc

CFLAGS		=	-Werror -Wextra -Wall -g# -ldl -lglfw -pthread -lm

INCLUDE		=	-Iincludes

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $@

$(NAME): $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFTDIR)/libft.a $(LIBMLX)/build/libmlx42.a -o $(NAME)

make_libft:
	make -C libft

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY:  all clean fclean re make_libft
