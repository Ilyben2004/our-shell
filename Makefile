CC = cc

CFLAGS = #-Wall -Wextra -Werror 

NAME = minishell


LIBFT = libft.a
SRCS = parsing.c utils1.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT) : 
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all