/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 20:29:05 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	varlen_env(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (*str == 0)
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

void	add_var_export(t_ms *t, char *str, int index)
{
	int		i;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	if (ft_strchr(str, '=') != 0)
		add_var_env(t, str, index);
	while (t->export[i] != NULL)
	{
		if (i == index)
			newenv[i++] = ft_strdup(str);
		newenv[i] = ft_strdup(t->export[i]);
		i++;
	}
	if (index < 0)
		newenv[i] = ft_strdup(str);
	i = 0;
	while (t->export[i] != NULL)
	{
		t->export[i] = pfree(t->export[i]);
		i++;
	}
	t->export = pfree(t->export);
	t->export = newenv;
	export_sort(t);
}

int	ft_export(t_ms *t, int i)
{
	int	index;

	t->j = 1;
	while (t->cmdl[i][t->j] != NULL)
	{
		index = 0;
		while (t->cmdl[i][t->j] != NULL && t->env[index] != NULL)
		{
			if (ft_strncmp(t->env[index], t->cmdl[i][t->j] \
			, varlen_env(t->cmdl[i][t->j])) == 0)
			{
				add_var_export(t, t->cmdl[i][t->j], index);
				index = -1;
				break ;
			}
			index++;
		}
		if (t->cmdl[i][t->j] != NULL && index > -1)
			add_var_export(t, t->cmdl[i][t->j], -1);
		t->j++;
	}
	if (t->cmdl[i][1] == NULL)
		printexport(t);
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

int	export_compare(t_ms *t, int i)
{
	int	lower;
	int	j;

	lower = 0;
	while (t->export[i] != NULL)
	{
		j = i + 1;
		t->temp = t->export[j];
		while (t->export[j] != NULL)
		{
			if (ft_strcmp(t->export[i], t->export[j]) > 0 && ft_strcmp(t->export[j], t->export[lower]) < 0)
				lower = j;
			j++;
		}
		t->temp = t->export[i];
		t->export[i] = t->export[lower];
		t->export[lower] = t->temp;
		i++;
	}
	return (i);
}

int	tab_sorted(char **lst)
{
	int		i;

	i = 0;
	while (lst[i] != NULL && lst[i + 1] != NULL)
	{
		if (*lst[i] > *lst[i + 1])
		{
			ft_swap(lst[i], lst[i + 1]);
			return (-1);
		}
		i++;
	}
	if (lst[i + 1] == NULL)
	{
		if (*lst[i] >= *lst[i - 1] && *lst[i] > *lst[0])
			return (0);
		else
			ft_swap(lst[i], lst[0]);
	}
	return (-1);

}

void	export_sort(t_ms *t)
{
	int	i;

	i = 0;
	while (tab_sorted(t->export) != 0)
	{
		i = 0;
		i = export_compare(t, i);
		t->export[i] = NULL;
	}
}
