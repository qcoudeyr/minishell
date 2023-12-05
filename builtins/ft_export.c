/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 17:13:50 by  qcoudeyr        ###   ########.fr       */
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
	int		j;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	j = 0;
	while (t->env[i] != NULL)
	{
			if (i == index)
			{
				newenv[j++] = ft_strdup(str);
				i++;
			}
			newenv[j++] = ft_strdup(t->env[i++]);
	}
	newenv[j] = ft_strdup(str);
	j = 0;
	while (t->env[j] != NULL)
		pfree(t->env[j++]);
	pfree(t->env);
	t->env = newenv;
}

void	ft_export(t_ms *t, int i)
{
	int		j;
	int		index;

	j = 1;
	while (t->cmdlist[i][j] != NULL)
	{
		index = 0;
		while(ft_strchr(t->cmdlist[i][j], '=') == 0)
			j++;
		while (t->env[index] != NULL)
		{
			if (ft_strncmp(t->env[index], t->cmdlist[i][j], varlen_env(t->cmdlist[i][j])) == 0)
			{
				add_var_env(t, t->cmdlist[i][j], index);
				index = -1;
				break ;
			}
			index++;
		}
		if (t->cmdlist[i][j] != NULL && index > -1)
			add_var_env(t, t->cmdlist[i][j], -1);
		j++;
	}

}
