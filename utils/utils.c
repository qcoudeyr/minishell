/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:50:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 11:22:26 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*tabfree(void **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return (ptr);
	while (ptr[i] != NULL)
	{
		ptr[i] = pfree(ptr[i]);
		i++;
	}
	ptr = pfree(ptr);
	return (NULL);
}

void	*pfree(void *ptr)
{
	if (ptr == NULL)
		return (NULL);
	else
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

int	is_special(char *str)
{
	if (str != NULL && (*str == '|' || *str == '&'))
		return (1);
	else
		return (0);
}

int	check_access(char *str)
{
	if (str != NULL && *str != 0)
	{
		if (access(str, X_OK) != 0)
			return (-1);
	}
	return (0);
}

int	tablen(void **tabl)
{
	int	index;

	index = 0;
	if (tabl == NULL || *tabl == NULL)
		return (0);
	while (tabl[index] != NULL)
		index++;
	return (index);
}
