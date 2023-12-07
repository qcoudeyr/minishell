/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:18:44 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/07 08:40:19 by  qcoudeyr        ###   ########.fr       */
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

void	heredoc_error(t_ms *t, int index, int i)
{
	if (t->cmdl[index + 1][0] != NULL)
		fd_printf(2, "syntax error near unexpected token \'%s\'\n", t->cmdl[index + 1][0]);
	else
		fd_printf(2, "syntax error near unexpected token \'\\n'\n");
	t->status = 512;
}

void	handle_heredoc(t_ms *t, int index, int i)
{
	char	*temp;

	if (t->cmdl[index][i + 1] == NULL || *t->cmdl[index][i + 1] == 0)
		return (heredoc_error(t, index, i));
	while ()
	temp = get_next_line(STDIN_FILENO);

}

void	input_redirect(t_ms *t, int index, int i)
{
	if (ft_strnstr(t->cmdl[index][i], "<<", 3) != 0)
	{
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
	if (ft_strnstr(t->cmdl[index][i], ">>", 3) != 0)
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
	t->cmdl[index][i] = NULL;
	t->cmdl[index][i + 1] = NULL;
	while (t->cmdl[index][i + 2] != NULL)
	{
		t->cmdl[index][i] = t->cmdl[index][i + 2];
		i++;
	}
}
