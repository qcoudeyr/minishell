/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/17 19:25:29 by lheinric         ###   ########.fr       */
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

int	ft_echo(char *cmd)
{
	int fd[0];
	t_echo echo;
	char	**ordre;

	fd[0] = 1;

	ordre = ft_split(cmd, ' ');
	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	find_redirect(fd, ordre);
	find_bn(&echo, ordre);
	print_echo(fd[0], &echo, ordre);
	free_tabstr(ordre);
	if (fd[0] > 1)
		close(fd[0]);
	return (1);
}
