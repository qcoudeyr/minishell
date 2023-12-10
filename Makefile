# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 22:29:45 by  qcoudeyr         #+#    #+#              #
#    Updated: 2023/12/10 20:08:59 by  qcoudeyr        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c %.o %.h %.a ./libft ./parsing ./error ./main ./builtins ./utils ./object
VPATH = . : ./libft : ./parsing : ./error : ./main : ./builtins : ./utils
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIB_DIR = ./libft/
LIBS = -lft -lreadline -lncurses -lhistory

HEADERS = minishell.h

SRCS =	main.c \
		parsing.c error.c bultinexe.c ft_cd.c ft_echo.c \
		remove_quotes.c find_redirect.c heredoc.c signal.c\
		env_var.c pipe.c bonus.c utils.c free.c exec.c \
		error_2.c env.c ft_unset.c ft_export.c init.c \
		ft_pwd.c export_utils.c import_env.c path.c

OBJDIR = ./object/
OBJS = $(addprefix $(OBJDIR),$(SRCS:.c=.o))

NAME = minishell

all: $(OBJDIR) $(NAME) norme generate_env

$(NAME): $(OBJS) libft
	@echo "\033[2m\033[31mStart to make $(NAME)\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) $(LIBS) -o $(NAME)
	@echo "\033[32m\t$(NAME) is done !\033[0m"

$(OBJDIR)%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I$(<D) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

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
	@rm -rf $(OBJDIR)
	@rm -rf ./utils/.env
	@rm -rf debug
	@echo "\033[32m\tFCLEAN is done!\033[0m"


re: fclean all


norme:
	@echo "\033[2m\033[31mLet's check the norme for $(NAME)\033[0m"
	@if [ $$(norminette | grep Error | wc -c) -eq 0 ]; then \
		echo "\033[32m\033[1m\tNorme is OK!\033[0m"; \
	else \
		echo "\033[31m\033[1m\tNorme is BAD!\033[0m"; \
		norminette | grep Error ;\
		echo "\033[31m\033[1mNEED TO FIX ALL OF THIS !!!\033[0m"; \
	fi

generate_env:
	@/usr/bin/env > ./utils/.env


debug: $(OBJS)
	@clear
	@$(CC) $(CFLAGS) -g $(OBJS) -L$(LIB_DIR) $(LIBS) -o debug
	colour-valgrind -s --tool=memcheck --leak-check=full --error-exitcode=1 \
	./debug

.PHONY: all clean fclean re debug libft norme generate_env

#--show-leak-kinds=all --track-origins=yes
