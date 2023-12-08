/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:57:13 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 11:01:15 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(t_ms *t)
{
	if (t->cmdl[t->i][t->j] != NULL && *t->cmdl[t->i][t->j] == '/' && \
ft_strnstr(t->cmdl[t->i][0], "echo", 5) == 0)
	{
		if (access(t->cmdl[t->i][t->j], X_OK) != 0)
		{
			perror("access");
			return (-1);
		}
	}
	return (0);
}

void	change_path(t_ms *t, int index)
{
	t->cmdl[index][0] = pfree(t->cmdl[index][0]);
	t->cmdl[index][0] = ft_strjoin(t->fpath, (char *) '\0');
	t->fpath = pfree(t->fpath);
}
