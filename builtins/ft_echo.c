/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/08 12:16:14 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*echo prend en charactere un fd (fichier ou sortie), la struct minishell comme d'habitude
et un tableau de string le tableau de string doit commencer juste apres la string
echo appelee.*/

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre, int i)
{
	if (ordre[i+1] == NULL && (ordre[i][0] == '-'
					&& ordre[i][1] == 'n'))
				{
					echo->nobackslash = 1;
					echo->no_bs_position = i;
				}
			else if (strncmp(ordre[i-1], "echo", 4) == 0 && (ordre[i][0] == '-'
					&& ordre[i][1] == 'n'))
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

int	ft_echo(int fd, t_ms *t, char **ordre)
{
	int i;
	int j;
	t_echo echo;

	(void)t;
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
