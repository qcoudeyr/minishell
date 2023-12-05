/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:01:23 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 16:22:49 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	varlen_env(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == 0)
		return (0);
	while (str[i] != 0 && str[i] != '=')
		i++;
	return (i);
}

void	remove_var_env(t_ms *t, int index)
{
	int		i;
	int		j;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	j = 0;
	while (t->env[i] != NULL && t->env[i + 1] != NULL)
	{
		if (i == index)
			i++;
		newenv[j++] = ft_strdup(t->env[i++]);
	}
	j = 0;
	while (t->env[j] != NULL)
		pfree(t->env[j++]);
	pfree(t->env);
	t->env = newenv;
}

void	ft_unset(t_ms *t, int i)
{
	int		j;
	int		index;

	j = 1;
	index = 0;
	while (t->cmdlist[i][j] != NULL)
	{

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
