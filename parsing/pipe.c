/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:18:22 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/27 11:38:51 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	have_pipe(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL && ft_strchr(cmds[i], '|') == 0)
		i++;
	if (cmds[i] != NULL && ft_strchr(cmds[i], '|') == 0)
		return (0);
	else
		return (1);
}

void	handle_pipe(t_ms *t)
{
	char	***temp_tab;
	int		i;
	int		index;
	int		j;

	i = 0;
	j = 0;
	index = 0;
	temp_tab = ft_calloc(100, sizeof(char **));
	temp_tab[index] = ft_calloc(100, sizeof(char *));
	while (t->cmdlist[0][j] != NULL)
	{
		if ((ft_strchr(t->cmdlist[0][j], '|') == 0 || is_or(t->cmdlist[0][j]) == 1) && is_and(t->cmdlist[0][j]) == 0)
			temp_tab[index][i++] = ft_strdup(t->cmdlist[0][j]);
		else
		{
			temp_tab[++index] = ft_calloc(1, sizeof(char *));
			temp_tab[index][0] = ft_strdup(t->cmdlist[0][j]);
			temp_tab[++index] = ft_calloc(100, sizeof(char *));
			i = 0;
		}
		j++;
	}
	free(t->cmdlist);
	t->cmdlist = temp_tab;
	t->ncmd = index + 1;
}
