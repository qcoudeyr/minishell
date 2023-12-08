/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:55:05 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 10:58:56 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tab_sorted(char **lst)
{
	int		i;

	i = 0;
	while (lst[i] != NULL && lst[i + 1] != NULL)
	{
		if (*lst[i] > *lst[i + 1])
			return (-1);
		i++;
	}
	if (lst[i + 1] == NULL)
	{
		if (*lst[i] >= *lst[i - 1] && *lst[i] > *lst[0])
			return (0);
	}
	return (-1);
}

void	export_compare(t_ms *t)
{
	int	i;
	int	j;

	i = 0;
	while (t->export[i] != NULL)
	{
		j = i + 1;
		while (t->export[j] != NULL)
		{
			if (ft_strcmp(t->export[i], t->export[j]) > 0)
			{
				t->temp = t->export[i];
				t->export[i] = t->export[j];
				t->export[j] = t->temp;
			}
			j++;
		}
		i++;
	}
}

void	export_sort(t_ms *t)
{
	while (tab_sorted(t->export) != 0)
		export_compare(t);
}

int	tab_sorted(char **lst)
{
	int		i;

	i = 0;
	while (lst[i] != NULL && lst[i + 1] != NULL)
	{
		if (*lst[i] > *lst[i + 1])
			return (-1);
		i++;
	}
	if (lst[i + 1] == NULL)
	{
		if (*lst[i] >= *lst[i - 1] && *lst[i] > *lst[0])
			return (0);
	}
	return (-1);
}
