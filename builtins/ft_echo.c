/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/04 12:55:45 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre)
{
	int	i;

	i = 0;
	while (ordre[i + 1] != NULL)
	{
		if (ft_strncmp(ordre[i], "-n", 3) == 0)
		{
			echo->no_bs_position = i;
			echo->nobackslash = 1;
			break ;
		}
		i++;
	}
}

void	print_echo(int fd, t_echo *echo, char **ordre)
{
	int	i;

	i = 0;
	while (ordre[++i] != NULL && ft_strncmp(ordre[i], ">", 2) != 0 && \
ft_strncmp(ordre[i], ">>", 3) != 0)
	{
		if (ft_strncmp(ordre[i], "-n", 3) != 0)
			fd_printf(fd, "%s ", ordre[i]);
	}
	if (echo->nobackslash == 0)
		fd_printf(fd, "\n");
}

int	ft_echo(t_ms *t, int i)
{
	t_echo	echo;

	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	find_bn(&echo, t->cmdlist[i]);
	print_echo(t->output_fd, &echo, t->cmdlist[i]);
	if (t->output_fd > 1)
		close(t->output_fd);
	return (1);
}
