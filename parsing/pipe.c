/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:18:22 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 09:25:11 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	have_pipe(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL && (ft_strchr(cmds[i], '|') == 0 || \
	cmds[i][0] == '\'' || cmds[i][0] == '\"'))
		i++;
	if (cmds[i] == 0 || (cmds[i] != NULL && ft_strchr(cmds[i], '|') == 0))
		return (0);
	else
		return (1);
}

void	handle_pipe(t_ms *t)
{
	char	***temp_tab;
	int		index;

	t->i = 0;
	t->j = 0;
	index = 0;
	temp_tab = ft_calloc(100, sizeof(char **));
	temp_tab[index] = ft_calloc(100, sizeof(char **));
	while (t->cmdl[0][t->j] != NULL)
	{
		if ((ft_strchr(t->cmdl[0][t->j], '|') == 0 || \
is_or(t->cmdl[0][t->j]) == 1) && is_and(t->cmdl[0][t->j]) == 0)
			temp_tab[index][t->i++] = ft_strdup(t->cmdl[0][t->j]);
		else
		{
			temp_tab[++index] = ft_calloc(100, sizeof(char *));
			temp_tab[index][0] = ft_strdup(t->cmdl[0][t->j]);
			temp_tab[++index] = ft_calloc(100, sizeof(char *));
			t->i = 0;
		}
		t->j++;
	}
	ft_freecmdl(t);
	t->cmdl = temp_tab;
	t->ncmd = index + 1;
}
