/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:01:23 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/12 19:26:49 by  qcoudeyr        ###   ########.fr       */
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

void	remove_var_export(t_ms *t, char *str)
{
	int		i;
	int		j;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	j = 0;
	while (t->export[i] != NULL)
	{
		if (str && !ft_strncmp(t->export[i], str, varlen_env(str)))
			i++;
		if (t->export[i] != NULL)
			newenv[j++] = ft_strdup(t->export[i++]);
	}
	t->export = tabfree((void **) t->export);
	t->export = newenv;
}

int	unset_error(t_ms *t, char *str)
{
	t->temp = pfree(t->temp);
	ft_printf("unset: %s: invalid parameter name\n", str);
	return (2);
}

int	is_alpha_only(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_ms *t, int i)
{
	t->j = 1;
	while (t->cmdl[i][t->j] != NULL)
	{
		t->temp = ft_strjoin(t->cmdl[i][t->j], "=");
		if (is_alpha_only(t->cmdl[i][t->j]) != 0)
			return (unset_error(t, t->cmdl[i][t->j]));
		t->i = 0;
		while (t->env[t->i] != NULL)
		{
			if (ft_strncmp(t->env[t->i], t->temp, \
	ft_strlen(t->temp)) == 0)
			{
				remove_var_env(t, t->i);
				break ;
			}
			t->i++;
		}
		remove_var_export(t, t->cmdl[i][t->j]);
		t->j++;
		t->temp = pfree(t->temp);
	}
	return (0);
}
