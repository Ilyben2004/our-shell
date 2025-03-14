CC = cc

CFLAGS = #-Wall -Wextra -Werror 

NAME = minishell


LIBFT = libft.a
SRCS = parsing.c utils1.c utils2.c mylibft.c extract_path.c tree_ops.c utils3.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(NAME)
	valgrind	./$(NAME)

$(LIBFT) : 
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
