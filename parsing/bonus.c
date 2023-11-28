/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:09:16 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/28 09:22:57 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_or(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i] != 0)
	{
		if (str[i] == '|' && str[i + 1] != 0 && str[i + 1] == '|')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
int	is_and(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i] != 0)
	{
		if (str[i] == '&' && str[i + 1] != 0 && str[i + 1] == '&')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	have_wildcard(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL && ft_strchr(cmds[i], '*') == 0)
		i++;
	if (cmds[i] != NULL && ft_strchr(cmds[i], '*') == 0)
		return (0);
	else
		return (1);
}
