/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/20 12:27:08 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre)
{
	int i;

	i = 0;
	while (ordre[i + 1] != NULL)
	{
		if (ft_strncmp(ordre[i], "-n", 3) == 0)
		{
			echo->no_bs_position = i;
			echo->nobackslash = 1;
			break;
		}
		i++;
	}
}

void	print_echo(int fd, t_echo *echo, char **ordre)
{
	int i;

	i = 0;
	while(ordre[++i] != NULL && ft_strncmp(ordre[i], ">", 2) != 0 && ft_strncmp(ordre[i], ">>", 3) != 0)
	{
		if (ft_strncmp(ordre[i], "-n", 3) != 0)
			fd_printf(fd, "%s ", ordre[i]);
	}
	if (echo->nobackslash == 0)
		fd_printf(fd, "\n");
}

int	ft_echo(char **cmd)
{
	int fd[0];
	t_echo echo;

	fd[0] = 1;
	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	find_redirect(fd, cmd);
	find_bn(&echo, cmd);
	print_echo(fd[0], &echo, cmd);
	if (fd[0] > 1)
		close(fd[0]);
	return (1);
}
