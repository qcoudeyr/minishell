vpath %.c %.o %.h %.a ./libft ./parsing ./error ./main

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIB_DIR = ./libft/
LIBS = -lft -lreadline -lncurses -lhistory

HEADERS = minishell.h

SRCS =	main.c parsing.c error.c cmdexe.c

OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) libft
	@echo "\033[2m\033[31mStart to make $(NAME)\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) $(LIBS) -o $(NAME)
	@echo "\033[32m\t$(NAME) is done !\033[0m"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@echo "\033[2m\033[31mCooking the LIBFT\033[0m"
	@$(MAKE) -s -C ./libft
	@echo "\033[32m\tLIBFT is done!\033[0m"

clean:
	@echo "\033[2m\033[31mStart to CLEAN\033[0m"
	@rm -f $(OBJS)
	@$(MAKE) -s -C ./libft clean
	@echo "\033[32m\tCLEAN is done!\033[0m"

fclean: clean
	@clear
	@echo "\033[2m\033[31mStart to FCLEAN\033[0m"
	@rm -f $(NAME)
	@$(MAKE) -s -C ./libft fclean
	@echo "\033[32m\tFCLEAN is done!\033[0m"

re: fclean all


norme:
	norminette $(SRCS) $(HEADERS)

debug: $(OBJS)
	@clear
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) $(LIBS) -o debug
	colour-valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 \
	./debug

.PHONY: all clean fclean re debug libft
