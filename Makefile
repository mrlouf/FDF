# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	fdf

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCLUDES	=	includes

LIBFTDIR	=	libft

LIBMLX		= 	mlx42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	

HEADER		=	$(INCLUDES)/fdf.h

MAKE		=	Makefile

OBJS		=	$(SRC:.c=.o)

LIBS		=	$(LIBFTDIR)/libft.a $(LIBMLX)/build/libmlx42.a

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			=	-cc
CFLAGS		=	-Werror -Wextra -Wall -g# -fsanitize=address
INCLUDE		=	-I/

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE)$(HEADER) libft/libft.a -o $(NAME)

make_libft:
	make -C libft

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE)$(HEADER) -c $< -o $@

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY:  all clean fclean re make_libft
