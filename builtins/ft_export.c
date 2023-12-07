/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 19:25:26 by  qcoudeyr        ###   ########.fr       */
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
		while (t->cmdl[i][j] != NULL && ft_strchr(t->cmdl[i][j], '=') == 0)
		{

		}
		while (t->cmdl[i][j] != NULL && t->env[index] != NULL)
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


int	printexport(t_ms *t)
{
	int	j;

	j = -1;
	while (t->export[++j] != NULL)
		fd_printf(t->output_fd, "%s\n", t->export[j]);
	return (0);
}

void	get_export(t_ms *t)
{
	t->export = ft_calloc((tablen((void **)t->env) + 1), sizeof(char *));
	t->i = 0;
	while (t->env[t->i] != NULL)
	{
		t->export[t->i] = ft_strdup(t->env[t->i]);
		t->i++;
	}
	t->export[t->i] = NULL;
}

void	export_compare(t_ms *t)
{
	int	lower;

	lower = 0;
	while (t->export[t->i] != NULL)
	{
		t->j = t->i + 1;
		t->temp = t->export[t->j];
		while (t->export[t->j] != NULL)
		{
			if (ft_strcmp(t->export[t->i], t->export[t->j]) > 0 && ft_strcmp(t->export[t->j], t->export[lower]) < 0)
				lower = t->j;
			t->j++;
		}
		t->temp = t->export[t->i];
		t->export[t->i] = t->export[lower];
		t->export[lower] = t->temp;
		t->i++;
	}
}

int	tab_sorted(char **lst)
{
	int		i;
	char	*temp;

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
		else
		{
			temp = lst[0];
			lst[0] = lst[i];
			lst[i] = temp;
		}
	}
	return (-1);

}

void	export_sort(t_ms *t)
{
	while (tab_sorted(t->export) != 0)
	{
		t->i = 0;
		export_compare(t);
		t->export[t->i] = NULL;
	}
}
