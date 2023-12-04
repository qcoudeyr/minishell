/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:50:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 10:50:31 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
