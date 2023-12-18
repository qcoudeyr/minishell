/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:08:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/18 11:03:25 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	if (signal != SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (signal != SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

void	handle_signal(t_ms *t)
{
	struct sigaction	act;

	bzero(&act, sizeof(act));
	act.sa_handler = &sigint_handler;
	if (sigaction(SIGINT, &act, NULL) == 0)
		t->signal = 1;
	sigaction(SIGQUIT, &act, NULL);
}
