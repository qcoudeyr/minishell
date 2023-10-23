vpath %.c %.h %.a ./libft ./parsing ./error ./main

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIB_DIR = ./libft/
LIBS = -lft -lreadline

HEADERS = minishell.h

SRCS =	main.c

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) $(LIBS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C ./libft

clean:
	rm -f $(OBJS)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all


norme:
	norminette $(SRCS) $(HEADERS)

debug: $(OBJS)
	clear
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o debug

	colour-valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
	./debug

.PHONY: all clean fclean re debug libft
