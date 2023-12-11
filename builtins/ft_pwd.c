/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:54:47 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/11 15:05:37 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_ms *t)
{
	int	i;

	i = 0;
	while (t->export[i] != NULL)
	{
		if (ft_strncmp(t->export[i], "PWD=", 3) == 0)
		{
			printf("%s\n", t->export[i] + 4);
			return (0);
		}
		i++;
	}
	return (512);
}
