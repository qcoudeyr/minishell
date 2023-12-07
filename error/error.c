/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 12:51:41 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmdnotfound(t_ms *t, char *str)
{
	(void) t;
	if (check_access(str) != 0 && is_builtins(str) == 0)
	{
		printf("Command not found: %s\n", str);
		t->status = 32512;
	}
	return (-1);
}

void	ft_acceserror(t_ms *t)
{
	if (errno == ENOENT)
		ft_printf("Input file does not exist.\n");
	else if (errno == EACCES)
		ft_printf("Input file is not readable or permission denied.\n");
	else
		ft_perror(t, "access");
	exit(EXIT_FAILURE);
}
