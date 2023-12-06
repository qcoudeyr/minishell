/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:43:26 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 10:45:20 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freecmdl(t_ms *t)
{
	int	i;

	i = 0;
	if (t->cmdl != NULL)
	{
		while (t->cmdl != NULL && t->cmdl[i] != NULL)
		{
			t->cmdl[i] = tabfree((void **) t->cmdl[i]);
			i++;
		}
		if (t->cmdl != NULL)
			t->cmdl = pfree(t->cmdl);
	}
}

void	ft_free(t_ms *t)
{
	t->cmd = tabfree((void **) t->cmd);
	t->path = tabfree((void **) t->path);
	t->env = tabfree((void **) t->env);
	t->home = pfree(t->home);
	t->rusage = pfree(t->rusage);
	t->pwd = pfree(t->pwd);
	t->fpath = pfree(t->fpath);
	t = pfree(t);
}
