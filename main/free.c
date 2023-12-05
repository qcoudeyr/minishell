/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:43:26 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 18:41:46 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freecmdlist(t_ms *t)
{
	int	i;
	int	j;

	i = 0;
	if (t->cmdlist != NULL)
	{
		while (t->cmdlist != NULL && t->cmdlist[i] != NULL)
		{
			j = -1;
			while (t->cmdlist[i][++j] != NULL)
				pfree(t->cmdlist[i][j]);
			pfree(t->cmdlist[i]);
			i++;
		}
		t->cmdlist = pfree(t->cmdlist);
	}
}

void	ft_free(t_ms *t)
{
	t->cmd = tabfree((void **) t->cmd);
	t->path = tabfree((void **) t->path);
	t->env = tabfree((void **) t->env);;
	pfree(t->home);
	pfree(t->rusage);
	pfree(t->pwd);
	pfree(t->fpath);
	pfree(t);
}
