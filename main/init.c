/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:56:19 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/17 11:43:06 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	t_init(t_ms *t)
{
	t->rusage = ft_calloc(1, sizeof(struct rusage));
	t->cmdl = NULL;
	t->cmd = ft_calloc(1000, sizeof(char *));
	t->path = ft_calloc(1, sizeof(char **));
	t->fpath = NULL;
	t->home = ft_calloc(1, sizeof(char *));
	t->pwd = ft_calloc(1, sizeof(char *));
	t->env = NULL;
	t->export = NULL;
	t->temp = NULL;
	t->ptr = NULL;
	t->index = 0;
	t->i = 0;
	t->j = 0;
	t->nc = 0;
	t->signal = 0;
	t->exit = 0;
	t->status = 0;
	t->return_v = 0;
	t->input_fd = 0;
	t->output_fd = 0;
	t->fd = 0;
}

void	init_cmdl(t_ms *t)
{
	if (t->cmdl != NULL)
		ft_freecmdl(t);
	t->cmdl = ft_calloc(10, sizeof(char **));
}

void	first_format(t_ms *t)
{
	t->cmd[t->nc] = format_path(rmcharq(t->cmd[t->nc], '\\'));
	t->cmd[t->nc] = spec_format(t->cmd[t->nc]);
	t->cmd[t->nc] = h_rpath(t, t->cmd[t->nc]);
}

void	change_path(t_ms *t, int index)
{
	t->cmdl[index][0] = pfree(t->cmdl[index][0]);
	t->cmdl[index][0] = ft_strjoin(t->fpath, (char *) '\0');
	t->fpath = pfree(t->fpath);
}
