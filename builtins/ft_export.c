/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 17:33:10 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			newenv[i] = ft_strdup(str);
		else
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

int	ft_export(t_ms *t, int i)
{
	int	index;

	t->j = 1;
	if (t->cmdl[i][1] == NULL || *t->cmdl[i][1] == '-')
		return (0 * printexport(t));
	while (t->cmdl[i][t->j] != NULL)
	{
		index = 0;
		while (t->cmdl[i][t->j] != NULL && t->export[index] != NULL)
		{
			if (ft_strncmp(t->export[index], t->cmdl[i][t->j] \
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
	export_sort(t);
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
