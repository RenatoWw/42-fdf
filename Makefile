NAME = fdf
CC = cc
# compilação
CFLAGS = -Wall -Werror -Wextra -Imlx -D BUFFER_SIZE=1
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm -Llibft/ -Lmlx -lft -lbsd
LIBFT = libft/
LIBFT_A = libft/libft.a

SRCS = fdf.c \
	free.c \
	parser.c \
	draw.c \
	init.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \


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