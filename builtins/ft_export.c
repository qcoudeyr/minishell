/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 20:00:55 by  qcoudeyr        ###   ########.fr       */
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

void	add_var_export(t_ms *t, char *str, int index)
{
	int		i;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
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
}

void	add_export_var(t_ms *t, char *str)
{
	int	ln;
	int	index;

	index = 0;
	ln = tablen(t->export);
	while (t->env[index] != NULL)
	{
		if (ft_strncmp(t->env[index], str \
		, varlen_env(str)) == 0)
		{
			add_var_env(t, str, index);
			index = -1;
			break ;
		}
		index++;
	}
	t->export[ln] = ft_strdup(str);
}


int	ft_export(t_ms *t, int i)
{
	t->j = 1;
	while (t->cmdl[i][t->j] != NULL)
	{
		t->index = 0;
		if (ft_strchr(t->cmdl[i][t->j], '=') == 0)
			add_export_var(t, t->cmdl[i][t->j]);
		while (t->cmdl[i][t->j] != NULL && t->env[t->index] != NULL)
		{
			if (ft_strncmp(t->env[t->index], t->cmdl[i][t->j] \
			, varlen_env(t->cmdl[i][t->j])) == 0)
			{
				add_var_env(t, t->cmdl[i][t->j], t->index);
				t->index = -1;
				break ;
			}
			t->index++;
		}
		if (t->cmdl[i][t->j] != NULL && t->index > -1)
			add_var_env(t, t->cmdl[i][t->j], -1);
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
	while (tab_sorted(t->export) != 0)
	{
		t->i = 0;
		export_compare(t);
		t->export[t->i] = NULL;
	}
}
