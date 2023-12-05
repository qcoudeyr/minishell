/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:43:26 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 18:59:58 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freecmdlist(t_ms *t)
{
	int	i;

	i = 0;
	if (t->cmdlist != NULL)
	{
		while (t->cmdlist != NULL && t->cmdlist[i] != NULL)
			t->cmdlist[i] = tabfree((void **) t->cmdlist[i++]);
		t->cmdlist = pfree(t->cmdlist);
	}
}

void	ft_free(t_ms *t)
{
	t->cmd = tabfree((void **) t->cmd);
	t->path = tabfree((void **) t->path);
	t->env = tabfree((void **) t->env);;
	t->home = pfree(t->home);
	t->rusage = pfree(t->rusage);
	t->pwd = pfree(t->pwd);
	t->fpath = pfree(t->fpath);
	t = pfree(t);
}
