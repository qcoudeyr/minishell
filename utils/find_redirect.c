/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:18:44 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/15 16:35:05 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redirect(t_ms *t, int i)
{
	int	y;

	y = 0;
	while ((ft_strncmp(t->cmdl[i][y], ">", 2) != 0 && \
ft_strncmp(t->cmdl[i][y], ">>", 3) != 0 && t->cmdl[i][y + 1] != NULL))
		y++;
	if (t->cmdl[i] != NULL)
	{
		if (ft_strncmp(t->cmdl[i][y], ">", 2) == 0)
			t->output_fd = open(t->cmdl[i][y +1], \
O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else if (ft_strncmp(t->cmdl[i][y], ">>", 3) == 0)
			t->output_fd = open(t->cmdl[i][y +1], \
O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		else
			t->output_fd = 1;
	}
	return (1);
}

void	input_redirect(t_ms *t, int index, int i)
{
	if (!is_vname(t->cmdl[index][i + 1]))
	{
		if (!t->cmdl[index][i + 1] && t->cmdl[index + 1])
			t->temp = t->cmdl[index + 1][0];
		else
			t->temp = t->cmdl[index][i + 1];
		ft_printf("minishell : syntax error near unexpected token "\
"`%s\'\n", t->temp);
		t->status = 512;
		t->return_v = 2;
	}
	else if (ft_strnstr(t->cmdl[index][i], "<<", 3) != 0)
	{
		if (access("./utils/temp", F_OK) != -1)
			unlink("./utils/temp");
		handle_heredoc(t, index, i);
	}
	else if (ft_strnstr(t->cmdl[index][i], "<", 2) != 0)
	{
		t->input_fd = open(t->cmdl[index][i + 1], O_RDONLY);
	}
	format_cmd_redirect(t, index, i);
}

void	output_redirect(t_ms *t, int index, int i)
{
	if (!is_vname(t->cmdl[index][i + 1]))
	{
		if (!t->cmdl[index][i + 1])
			t->temp = t->cmdl[index + 1][0];
		else
			t->temp = t->cmdl[index][i + 1];
		ft_printf("minishell : syntax error near unexpected token "\
"`%s\'\n", t->temp);
		t->status = 512;
		t->return_v = 2;
	}
	else if (ft_strnstr(t->cmdl[index][i], ">>", 3) != 0)
	{
		t->output_fd = open(t->cmdl[index][i + 1], \
O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	}
	else if (ft_strnstr(t->cmdl[index][i], ">", 2) != 0)
	{
		t->output_fd = open(t->cmdl[index][i + 1], \
O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	}
	format_cmd_redirect(t, index, i);
}

void	format_cmd_redirect(t_ms *t, int index, int i)
{
	int	j;

	t->cmdl[index][i] = pfree(t->cmdl[index][i]);
	t->cmdl[index][i + 1] = pfree(t->cmdl[index][i + 1]);
	j = i + 2;
	while (t->cmdl[index][j] != NULL)
	{
		t->cmdl[index][i] = sf_rplc(t->cmdl[index][i], t->cmdl[index][j]);
		t->cmdl[index][j] = NULL;
		i++;
		j++;
	}
}
