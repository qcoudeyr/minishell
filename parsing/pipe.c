/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:18:22 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 19:20:35 by  qcoudeyr        ###   ########.fr       */
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

int	pipe_in_q(char *str)
{
	int	i;
	int	quote;

	if (str == NULL)
		return (0);
	i = 0;
	quote = 0;
	while (str[i] != 0)
	{
		if (is_quote(str[i]) != 0)
			quote += 1;
		if (str[i] == '|' && (quote % 2) == 0)
			return (1);
		i++;
	}
	return (0);
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
		if ((pipe_in_q(t->cmdl[0][t->j]) == 0 && is_or(t->cmdl[0][t->j]) == 0) && is_and(t->cmdl[0][t->j]) == 0)
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
}
