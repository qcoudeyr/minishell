/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:50:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 10:34:18 by  qcoudeyr        ###   ########.fr       */
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
