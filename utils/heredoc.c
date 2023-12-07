/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 09:05:39 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 10:38:10 by  qcoudeyr        ###   ########.fr       */
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

	t->input_fd = open("./utils/temp",
O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (t->cmdl[index][i + 1] == NULL || *t->cmdl[index][i + 1] == 0)
		return (heredoc_error(t, index));
	temp = NULL;
	stop = ft_strjoin(t->cmdl[index][i + 1], "\n");
	while (ft_strnstr(temp, stop, ft_strlen(stop)) == 0)
	{
		if (temp != NULL)
			write(t->input_fd, temp, ft_strlen(temp));
		temp = pfree(temp);
		write(1, BOLD" -> "RESET, 13);
		temp = get_next_line(STDIN_FILENO);
	}
	get_next_line(-1);
	close(t->input_fd);
	t->input_fd = open("./utils/temp",O_RDONLY);
	temp = pfree(temp);
	stop = pfree(stop);
}
