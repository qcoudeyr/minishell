/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/06 11:09:13 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*echo prend en charactere un fd (fichier ou sortie), la struct ms comme d'habitude
et un tableau de string le tableau de string doit commancer juste apres la string
echo appelee.*/

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre, int i)
{
	if (ordre[i + 1] == NULL && \
	(ordre[i][0] == '-' && ordre[i][1] == 'n'))
	{
		echo->nobackslash = 1;
		echo->no_bs_position = i;
	}
	else if (ft_strncmp(ordre[i-1], "echo", 5) == 0 && \
	(ordre[i][0] == '-' && ordre[i][1] == 'n'))
	{
		echo->nobackslash = 1;
		echo->no_bs_position = i;
	}
}

void	print_echo(int fd, t_echo *echo, char **ordre)
{
	int i;

	i = -1;
	while(ordre[++i] != NULL)
	{
		if (i != echo->no_bs_position)
			fd_printf(fd, "%s", ordre[i]);
	}
	if (echo->nobackslash == 0)
		fd_printf(fd, "\n");
}

int	ft_echo(int fd, char **ordre)
{
	int i;
	int j;
	t_echo echo;

	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	i = -1;
	while(ordre[++i] != NULL)
	{
		j = -1;
		while (ordre[i][++j])
		{
			find_bn(&echo, ordre, i);
		}
	}
	print_echo(fd, &echo, ordre);
	return (0);
}
