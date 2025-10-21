NAME = fdf
CC = cc
# compilação
CFLAGS = -Wall -Werror -Wextra -Iincludes/mlx -D BUFFER_SIZE=1000 -Ofast
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm -Lincludes/libft/ -Lincludes/mlx -lft -lbsd
LIBFT = includes/libft/
LIBFT_A = includes/libft/libft.a

SRCS = fdf.c \
	free.c \
	map_functions/map_parser.c \
	map_functions/map_allocator.c \
	map_functions/map_filler.c \
	draw.c \
	draw_utils.c \
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