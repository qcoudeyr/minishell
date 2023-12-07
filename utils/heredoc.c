/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:05:39 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 09:35:06 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_error(t_ms *t, int index)
{
	if (t->cmdl[index + 1][0] != NULL)
		fd_printf(2, "syntax error near unexpected token \'%s\'\n", \
t->cmdl[index + 1][0]);
	else
		fd_printf(2, "syntax error near unexpected token \'\\n'\n");
	t->status = 512;
}

void	handle_heredoc(t_ms *t, int index, int i)
{
	char	*temp;
	char	*stop;

	if (t->cmdl[index][i + 1] == NULL || *t->cmdl[index][i + 1] == 0)
		return (heredoc_error(t, index));
	temp = NULL;
	stop = ft_strjoin(t->cmdl[index][i + 1], "\n");
	while (ft_strnstr(temp, stop, ft_strlen(temp)) == 0)
	{
		t->temp = temp;
		temp = ft_strjoin(temp, get_next_line(STDIN_FILENO));
		t->temp = pfree(t->temp);
	}
	close(STDIN_FILENO);
	temp[ft_strlen(temp) - 1] = 0;
	write(t->input_fd, temp, ft_strlen(temp) + 1);
	temp = pfree(temp);
	stop = pfree(stop);
}
