/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:18:22 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/17 12:01:51 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	have_meta(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL && ((ft_strchr(cmds[i], '|') == 0 \
	&& ft_strchr(cmds[i], '&') == 0) || ft_strchr("\'\"", cmds[i][0])))
		i++;
	if (cmds[i] == 0 || (cmds[i] != NULL && (!ft_strchr(cmds[i], '|') \
	&& !ft_strchr(cmds[i], '&'))))
		return (0);
	else
		return (1);
}

int	m_in_q(char *str)
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
		if (ft_strchr("|&", str[i]) && (quote % 2) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	handle_m(t_ms *t)
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
		if ((m_in_q(t->cmdl[0][t->j]) == 0 && \
is_or(t->cmdl[0][t->j]) == 0) && is_and(t->cmdl[0][t->j]) == 0)
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

void	end_pipe(t_ms *t)
{
	t->input_fd = t->pipefd[0];
	if (t->cmdl[t->index + 2] != NULL && \
	ft_strnstr(t->cmdl[t->index + 2][0], "|", 2) != 0)
	{
		if (pipe(t->pipefd) == -1)
			perror("pipe");
		else
		{
			close(t->output_fd);
			t->output_fd = t->pipefd[1];
		}
	}
	else
	{
		close(t->pipefd[1]);
		t->output_fd = STDOUT_FILENO;
	}
	t->index++;
}
