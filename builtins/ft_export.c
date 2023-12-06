/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 09:26:15 by  qcoudeyr        ###   ########.fr       */
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

void	add_var_env(t_ms *t, char *str, int index)
{
	int		i;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	while (t->env[i] != NULL)
	{
		if (i == index)
			newenv[i++] = ft_strdup(str);
		newenv[i] = ft_strdup(t->env[i]);
		i++;
	}
	if (index < 0)
		newenv[i] = ft_strdup(str);
	i = 0;
	while (t->env[i] != NULL)
	{
		t->env[i] = pfree(t->env[i]);
		i++;
	}
	t->env = pfree(t->env);
	t->env = newenv;
}

int	ft_export(t_ms *t, int i)
{
	int		j;
	int		index;

	j = 1;
	while (t->cmdl[i][j] != NULL)
	{
		index = 0;
		while (ft_strchr(t->cmdl[i][j], '=') == 0)
			j++;
		while (t->env[index] != NULL)
		{
			if (ft_strncmp(t->env[index], t->cmdl[i][j] \
			, varlen_env(t->cmdl[i][j])) == 0)
			{
				add_var_env(t, t->cmdl[i][j], index);
				index = -1;
				break ;
			}
			index++;
		}
		if (t->cmdl[i][j] != NULL && index > -1)
			add_var_env(t, t->cmdl[i][j], -1);
		j++;
	}
	return (0);
}
