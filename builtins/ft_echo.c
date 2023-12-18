/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/17 12:31:57 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre)
{
	int	i;

	i = 0;
	if (ordre[1] && ordre[1][0] == '-')
		i++;
	else
		return ;
	while (ordre[1] && ordre[1][i] != 0 && ordre[1][i] == 'n')
		i++;
	if (ordre[1][i] == 0)
	{
		echo->nobackslash = 1;
		echo->no_bs_position = 1;
	}
	return ;
}

void	print_echo(int fd, t_echo *echo, char **ordre)
{
	int	i;

	i = 0;
	while (ordre[++i] != NULL)
	{
		if (i != echo->no_bs_position)
			fd_printf(fd, "%s", ordre[i]);
	}
	if (echo->nobackslash == 0)
		fd_printf(fd, "\n");
}

int	ft_echo(t_ms *t, int i)
{
	t_echo	echo;

	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	find_bn(&echo, t->cmdl[i]);
	print_echo(t->output_fd, &echo, t->cmdl[i]);
	return (0);
}
