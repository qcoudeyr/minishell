/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:33:59 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/24 09:12:37 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	pathfinder(t_ms *t)
{
	int	i;
	int	arg;

	arg = 0;
	while (arg < t->narg+1)
	{
		i = 0;
		t->fpath = ft_strjoin(t->path[i], t->cmdlist[arg][0]);
		while (access (t->fpath, X_OK) < 0 && t->path[i + 1] != NULL)
		{
			i++;
			free(t->fpath);
			t->fpath = ft_strjoin(t->path[i], t->cmdlist[arg][0]);
		}
		if (access(t->fpath, X_OK) == 0)
		{
			free(t->cmdlist[arg][0]);
			t->cmdlist[arg][0] = ft_strdup(t->fpath);
		}
		else
			ft_cmdnotfound(t, t->cmdlist[arg][0]);
		arg++;
		free(t->fpath);
		t->fpath = NULL;
	}
}

void	cmdformat(t_ms *t)
{
	int		i;

	i = 0;
	t->cmdlist = ft_calloc((t->narg +1), sizeof(char **));
	while (i <= t->narg)
	{
		t->cmdlist[i] = ft_splitq(t->cmd[i]);
		i++;
	}
	pathfinder(t);
}

void	env_pars(t_ms *t)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strnstr(t->env[i], "PATH=", 6) == 0)
		i++;
	t->env[i] += 5;
	t->path = ft_split(t->env[i], ':');
	i = 0;
	while (t->path[i])
	{
		temp = ft_strdup(t->path[i]);
		free(t->path[i]);
		t->path[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}
