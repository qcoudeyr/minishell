/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 21:20:14 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	sigint_handler(int signo)
{
	(void)signo;

}

void	nothing_handler(int signo)
{
	(void)signo;
}

void	getsignal(int signal_number)
{
	if (signal_number == 2)
		signal(SIGINT, sigint_handler);
	else if (signal_number == 3)
		signal(SIGQUIT, nothing_handler);
} */

int	ft_cmdnotfound(t_ms *t, char *str)
{
	(void) t;
	if (check_path(str) != 0 && is_builtins(str) == 0)
	{
		printf("Command not found: %s\n", str);
		t->status = 32512;
	}
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
