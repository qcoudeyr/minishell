/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/29 10:36:20 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	nothing_handler(int signo)
{
	(void)signo;
}

void getsignal(int signal_number)
{
	if (signal_number == 2)
		signal(SIGINT, sigint_handler);
	else if (signal_number == 3)
	signal(SIGQUIT, nothing_handler);
}


int	ft_cmdnotfound(t_ms *t, int index)
{
	(void) t;
	if (check_path(t, index))
		printf("Command not found: %s\n",t->cmdlist[index][0]);
	return (-1);
}

void	ft_acceserror(t_ms *t)
{
	if (errno == ENOENT)
		ft_printf("Input file does not exist.\n");
	else if (errno == EACCES)
		ft_printf("Input file is not readable or permission denied.\n");
	else
		ft_perror(t, "access");
	exit(EXIT_FAILURE);
}

void	ft_perror(t_ms *t, char *s)
{
	if (s != NULL)
		perror(s);
	write(t->output_fd, "1", 1);
	exit(EXIT_FAILURE);
}
