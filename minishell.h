/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:33:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/01 21:15:35 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>
# include <stdlib.h>
# include <term.h>
# include "./libft/libft.h"
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>

typedef struct s_echo
{
	int	nobackslash;
	int	no_bs_position;
}t_echo;

typedef struct s_minishell
{
	char			***cmdlist;
	pid_t			pid;
	char			**cmd;
	int				narg;
	char			*fpath;
	int				status;
	int				ncmd;
	int				input_fd;
	int				output_fd;
	int				pipefd[2];
	char			**env;
	char			**path;
	char			*pwd;
	char			*home;
	char			*prev_pwd;
	struct rusage	*rusage;

}t_ms;

//		builtins
int		is_builtins(char *str);
int		ft_cd(t_ms *t, char *path);
int		ft_echo(t_ms *t, int i);
//		utils
int		check_path(char *str);
int		is_or(char *str);
char	*rmcharq(char *str, char c);
int		have_wildcard(char **cmds);
void	input_redirect(t_ms *t, int index, int i);
void	output_redirect(t_ms *t, int index, int i);
void	format_cmd_redirect(t_ms *t, int index, int i);
void	handle_redirect(t_ms *t, int index);
int		cmd_handler(t_ms *t);
void	exec_cmd(t_ms *t);
int		is_and(char *str);
void	handle_builtins(t_ms *t, int i);
void	handle_pipe(t_ms *t);
int		is_special(char *str);
void	ft_freecmdlist(t_ms *t);
void	init_cmdlist(t_ms *t);
void	*pfree(void *ptr);
int		have_pipe(char **cmds);
char	*remove_quotes(char *input);
void	free_tabstr(char **strs);
int		find_redirect(t_ms *t, int i);
char	*env_var(t_ms *t, char *str);
char	*handle_env_var(t_ms *t, char *str);
int		cmdformat(t_ms *t);
int		pathfinder(t_ms *t, int index);
int		ft_cmdnotfound(t_ms *t, char *str);
int		change_env(t_ms *t, char *var, char *tochange);
void	env_pars(t_ms *t);
void	ft_acceserror(t_ms *t);
void	ft_perror(t_ms *t, char *s);
void	ft_free(t_ms *t);
void	sigint_handler(int signo);
void	nothing_handler(int signo);
void	getsignal(int signal_number);


// Text colors
# define CL_BLACK   "\033[30m"
# define CL_RED     "\033[31m"
# define CL_GREEN   "\033[32m"
# define CL_YELLOW  "\033[33m"
# define CL_BLUE    "\033[34m"
# define CL_MAGENTA "\033[35m"
# define CL_CYAN    "\033[36m"
# define CL_WHITE   "\033[37m"

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
