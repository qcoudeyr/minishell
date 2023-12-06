/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 21:08:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 21:15:47 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return (void);
}

void	handle_signal(t_ms *t)
{
	struct sigaction	act;

//	Initialize structure to 0.
	bzero(&act, sizeof(act));
//	Add new signal handler
	act.sa_handler = &sigint_handler;
//	Apply new signal handler to SIGINT (ctrl-c)
	sigaction(SIGINT, &act, NULL);
}
