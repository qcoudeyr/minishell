/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/15 22:01:37 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_bn(t_echo *echo, char **ordre, int i)
{
	if (ordre[i+1] == NULL && (ordre[i][0] == '-' \
	&& ordre[i][1] == 'n'))
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
		if (i != echo->no_bs_position && i != 0)
			fd_printf(fd, "%s ", ordre[i]);
	}
	if (echo->nobackslash == 0)
		fd_printf(fd, "\n");
}

int	ft_echo(char *cmd)
{
	int fd;
	t_echo echo;
	char	**ordre;

	fd = 1;

	ordre = ft_split(cmd, ' ');
	echo.nobackslash = 0;
	echo.no_bs_position = -1;
	find_redirect(&fd, ordre);
	print_echo(fd, &echo, ordre);
	free_tabstr(ordre);
	return (1);
}
