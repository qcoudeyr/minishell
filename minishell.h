/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:33:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/25 10:39:51 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <term.h>
#include "./libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_heco
{
	int	nobackslash;
	int	no_bs_position;
}t_heco;

typedef struct s_minishell
{
	int		file_fd[2];
	char	***cmdlist;
	pid_t	pid;
	char	*infile;
	char	*outfile;
	char	**cmd;
	int		narg;
	char	*fpath;
	int		status;
	int		pipefd[2];
	char	**env;
	char	**path;
	char	*pwd;

}t_ms;

int		cmdformat(t_ms *t);
int		pathfinder(t_ms *t);
int		ft_cmdnotfound(t_ms *t, char *str);
int		is_builtins(t_ms *t, int i);
void	env_pars(t_ms *t);
void	ft_acceserror(t_ms *t);
void	ft_perror(t_ms *t, char *s);
void	ft_free(t_ms *t);
void	sigint_handler(int signo);
void	nothing_handler(int signo);
void	getsignal();

// Text colors
# define COLOR_BLACK   "\033[30m"
# define COLOR_RED     "\033[31m"
# define COLOR_GREEN   "\033[32m"
# define COLOR_YELLOW  "\033[33m"
# define COLOR_BLUE    "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN    "\033[36m"
# define COLOR_WHITE   "\033[37m"

// Background colors
# define BG_BLACK   "\033[40m"
# define BG_RED     "\033[41m"
# define BG_GREEN   "\033[42m"
# define BG_YELLOW  "\033[43m"
# define BG_BLUE    "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN    "\033[46m"
# define BG_WHITE   "\033[47m"

// Text attributes
# define RESET     "\033[0m"
# define BOLD      "\033[1m"
# define DIM       "\033[2m"
# define UNDERLINE "\033[4m"
# define BLINK     "\033[5m"
# define REVERSE   "\033[7m"
# define HIDDEN    "\033[8m"

#endif
