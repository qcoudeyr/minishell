/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:33:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 19:12:52 by  qcoudeyr        ###   ########.fr       */
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

typedef struct s_henv
{
	int		quote;
	int		squote;
	int		fquote;
	int		i;
	int		j;
	int		env_var;
	int		len;
	char	*var;
	char	*newstr;

}	t_env;

typedef struct s_minishell
{
	pid_t			pid;
	int				index;
	int				i;
	int				j;
	int				nc;
	int				signal;
	int				exit;
	int				status;
	int				return_v;
	int				input_fd;
	int				output_fd;
	int				fd;
	int				pipefd[2];
	void			*temp;
	char			*pwd;
	char			*home;
	char			*fpath;
	char			**path;
	char			**export;
	char			**env;
	char			**cmd;
	char			***cmdl;
	struct rusage	*rusage;
}t_ms;

//		builtins
int		is_builtins(char *str);
int		ft_cd(t_ms *t, char **path);
int		printexport(t_ms *t);
int		ft_echo(t_ms *t, int i);
int		ft_unset(t_ms *t, int i);
int		ft_pwd(t_ms *t);
void	remove_var_env(t_ms *t, int index);
int		varlen_env(char *str);
int		ft_export(t_ms *t, int i);
void	add_var_env(t_ms *t, char *str, int index);

//		utils
int		is_quote(char c);
void	*tabfree(void **ptr);
void	import_env(t_ms *t);
int		check_path(t_ms *t);
int		ask_for_env(t_ms *t);
void	change_path(t_ms *t, int index);
void	handle_signal(t_ms *t);
int		is_set_env_var(char *str);
void	get_env(t_ms *t, char **env);
void	end_pipe(t_ms *t);
void	t_init(t_ms *t);
void	handle_spec(t_ms *t);
void	change_str_env(t_env *e, t_ms *t, char *str);
void	hev_quote(char c, int *squote, int *quote, int *fquote);
int		check_path(t_ms *t);
int		check_access(char *str);
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
int		tablen(void **tabl);
void	ft_freecmdl(t_ms *t);
void	init_cmdl(t_ms *t);
void	t_init(t_ms *t);
void	*pfree(void *ptr);
int		have_pipe(char **cmds);
char	*remove_quotes(char *input);
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
int		ft_exit(t_ms *t);
void	sigint_handler(int signo);
void	nothing_handler(int signo);
void	getsignal(int signal_number);
void	handle_heredoc(t_ms *t, int index, int i);
void	get_export(t_ms *t);
void	export_sort(t_ms *t);

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
