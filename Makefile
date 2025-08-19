NAME = fdff

CC = cc
# compilação
CFLAGS = -Wall -Wextra -Werror -Imlx
# linkagem
LFLAGS = -lmlx -lXext -lX11 -lm

SRCS = fdf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re