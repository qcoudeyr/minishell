/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:56:19 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 13:50:20 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	t_init(t_ms *t)
{
	t->rusage = ft_calloc(1, sizeof(struct rusage));
	t->cmdl = NULL;
	t->cmd = ft_calloc(10000, sizeof(char *));
	t->path = ft_calloc(1, sizeof(char **));
	t->fpath = NULL;
	t->home = ft_calloc(1, sizeof(char *));
	t->pwd = ft_calloc(1, sizeof(char *));
	t->nc = 0;
	t->i = 0;
	t->j = 0;
}

void	init_cmdl(t_ms *t)
{
	if (t->cmdl != NULL)
		ft_freecmdl(t);
	t->cmdl = ft_calloc(10, sizeof(char **));
}
