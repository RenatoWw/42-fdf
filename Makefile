NAME = fdf
CC = cc
# compilação
CFLAGS = -Wall -Werror -Wextra -Imlx -D BUFFER_SIZE=1000
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm -Lincludes/libft/ -Lmlx -lft -lbsd
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a

SRCS = fdf.c \
	free.c \
	mapper/map_parser.c \
	mapper/map_allocator.c \
	mapper/map_filler.c \
	draw.c \
	init.c \
	colors.c \
	includes/gnl/get_next_line.c \
	includes/gnl/get_next_line_utils.c \


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME)

$(LIBFT_A):
	$(MAKE) -s -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re