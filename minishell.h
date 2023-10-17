/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:33:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/17 14:39:08 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>      // Pour printf
#include <stdlib.h>     // Pour malloc, free, exit
#include <string.h>     // Pour strerror
#include <unistd.h>     // Pour access, open, read, write, close, fork, getpid, getppid, getuid, getgid
#include <sys/wait.h>   // Pour wait, waitpid, wait3, wait4
#include <signal.h>     // Pour signal, sigaction, sigemptyset, sigaddset, kill
#include <dirent.h>     // Pour opendir, readdir, closedir
#include <sys/stat.h>   // Pour stat, lstat, fstat
#include <fcntl.h>      // Pour O_RDONLY, O_WRONLY, O_CREAT, etc.
#include <readline/readline.h> // Pour readline
#include <readline/history.h> // Pour rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
#include <ncurses.h>   // Pour les fonctions de ncurses comme tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <termios.h>    // Pour tcgetattr, tcsetattr
#include <sys/ioctl.h>  // Pour ioctl
#include <pwd.h>



/*// Text colors
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
# define HIDDEN    "\033[8m"*/

#endif
