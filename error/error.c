/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/24 08:48:28 by  qcoudeyr        ###   ########.fr       */
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

void	getsignal()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, nothing_handler);
}


void	ft_cmdnotfound(t_ms *t)
{
	perror("Command not found !");
	ft_free(t);
	exit(EXIT_FAILURE);
}

void	ft_acceserror(t_ms *t)
{
	if (errno == ENOENT)
		ft_printf("Input file does not exist.\n");
	else if (errno == EACCES)
		ft_printf("Input file is not readable or permission denied.\n");
	else
		ft_perror(t, "access");
	ft_free(t);
	exit(EXIT_FAILURE);
}

void	ft_perror(t_ms *t, char *s)
{
	if (s != NULL)
		perror(s);
	write(t->file_fd[1], "1", 1);
	ft_free(t);
	exit(EXIT_FAILURE);
}
