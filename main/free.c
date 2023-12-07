/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:43:26 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 09:48:28 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freecmdl(t_ms *t)
{
	int	i;

	i = 0;
	if (t->cmdl != NULL)
	{
		while (t->cmdl[i] != NULL)
		{
			t->cmdl[i] = tabfree((void **) t->cmdl[i]);
			i++;
		}
		t->cmdl = pfree(t->cmdl);
	}
}

void	ft_free(t_ms *t)
{
	while (t->nc >= 0)
	{
		t->cmd[t->nc] = pfree(t->cmd[t->nc]);
		t->nc--;
	}
	if (access("./utils/temp", F_OK) != -1)
		unlink("./utils/temp");
	t->cmd = pfree(t->cmd);
	t->path = tabfree((void **) t->path);
	t->env = tabfree((void **) t->env);
	t->home = pfree(t->home);
	t->rusage = pfree(t->rusage);
	t->pwd = pfree(t->pwd);
	t->fpath = pfree(t->fpath);
	t = pfree(t);
}
