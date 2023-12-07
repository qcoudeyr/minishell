/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:05:39 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 10:02:00 by  qcoudeyr        ###   ########.fr       */
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
	char	*buf;
	char	*stop;

	t->input_fd = open("./utils/temp", \
O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (t->cmdl[index][i + 1] == NULL || *t->cmdl[index][i + 1] == 0)
		return (heredoc_error(t, index));
	buf = NULL;
	temp = NULL
	stop = ft_strjoin(t->cmdl[index][i + 1], "\n");
	while (ft_strnstr(buf, stop, ft_strlen(buf)) == 0)
	{
		if (temp != NULL)
		{
			t->temp = buf;
			buf = ft_strjoin(temp, buf);
		}
		temp = get_next_line(STDIN_FILENO);
		t->temp = pfree(t->temp);
		temp = pfree(temp);
	}
	get_next_line(-1);
	buf[ft_strlen(buf) - 1] = 0;
	write(t->input_fd, temp, ft_strlen(temp));
	temp = pfree(temp);
	buf = pfree(buf);
	stop = pfree(stop);
}
