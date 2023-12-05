/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:01:23 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 19:08:45 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_var_env(t_ms *t, int index)
{
	int		i;
	int		j;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	j = 0;
	while (t->env[i] != NULL)
	{
		if (i == index)
			i++;
		if (t->env[i] != NULL)
			newenv[j++] = ft_strdup(t->env[i++]);
	}
	t->env = tabfree((void **) t->env);
	t->env = newenv;
}

void	ft_unset(t_ms *t, int i)
{
	int		j;
	int		index;

	j = 1;
	while (t->cmdlist[i][j] != NULL)
	{
		index = 0;
		while (t->env[index] != NULL)
		{
			if (ft_strncmp(t->env[index], t->cmdlist[i][j], ft_strlen(t->cmdlist[i][j])) == 0)
			{
				remove_var_env(t, index);
				break ;
			}
			index++;
		}
		j++;
	}

}
