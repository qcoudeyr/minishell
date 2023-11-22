/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:18:44 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/22 11:40:04 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redirect(t_ms *t, int i)
{
	while ((ft_strncmp(t->cmdlist[i], ">", 2) != 0 && ft_strncmp(t->cmdlist[i], ">>", 3) != 0 && t->cmdlist[i + 1] != NULL))
		i++;
	if (t->cmdlist[i] != NULL)
	{
		if(ft_strncmp(t->cmdlist[i], ">", 2) == 0)
			t->file_fd = open(t->cmdlist[i+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else if (ft_strncmp(t->cmdlist[i], ">>", 3) == 0)
			t->file_fd = open(t->cmdlist[i+1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		else
			t->file_fd = 1;
	}
	return 1;
}

void	handle_heredoc(t_ms *t, int index, int i)
{
	get_next_line()->cmdlist[index][i + 1]

}

void	input_redirect(t_ms *t, int index, int i)
{
		if (ft_strnstr(t->cmdlist[index][i], "<<", 3) != 0)
		{
			handle_heredoc(t);
		}
		else if (ft_strnstr(t->cmdlist[index][i], "<", 2) != 0)
		{
			t->input_fd = open(t->cmdlist[index][i + 1], O_RDONLY);
		}
}

void	output_redirect(t_ms *t, int index, int i)
{
	if (ft_strnstr(t->cmdlist[index][i], ">>", 3) != 0)
	{
		t->file_fd = open(t->cmdlist[index][i + 1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	}
	else if (ft_strnstr(t->cmdlist[index][i], ">", 2) != 0)
	{
		t->file_fd = open(t->cmdlist[index][i + 1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	}
}


