/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:02:42 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 10:51:07 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	path_format(t_ms *t)
{
	char	*temp;
	int		i;

	i = 0;
	while (t->path[i] != NULL)
	{
		temp = ft_strdup(t->path[i]);
		t->path[i] = pfree(t->path[i]);
		t->path[i] = ft_strjoin(temp, "/");
		temp = pfree(temp);
		i++;
	}
}

void	env_pars(t_ms *t)
{
	int		i;

	i = 0;
	t->path = tabfree((void **)t->path);
	t->pwd = pfree(t->pwd);
	t->home = pfree(t->home);
	while (t->env[i] != NULL)
	{
		if (ft_strnstr(t->env[i], "PATH=", 6) != 0)
			t->path = ft_split((t->env[i] + 5), ':');
		if (ft_strnstr(t->env[i], "PWD=", 5) != 0)
			t->pwd = ft_strdup(t->env[i] + 4);
		if (ft_strnstr(t->env[i], "HOME=", 6) != 0)
			t->home = ft_strdup(t->env[i] + 5);
		i++;
	}
	if (t->path != NULL)
		path_format(t);
}

void	env_var_detect(t_ms *t)
{
	int		i;
	char	*tmp;

	i = 0;
	while (t->cmdl[0][i] != NULL)
	{
		if (ft_strnstr(t->cmdl[0][i], "$?", 1) != 0)
		{
			t->cmdl[0][i] = pfree(t->cmdl[0][i]);
			t->cmdl[0][i] = ft_itoa(t->return_v);
		}
		else if (ft_strnstr(t->cmdl[0][i], "$", 1) != 0)
		{
			tmp = env_var(t, t->cmdl[0][i]);
			if (tmp != NULL)
			{
				t->cmdl[0][i] = pfree(t->cmdl[0][i]);
				t->cmdl[0][i] = tmp;
			}
		}
		i++;
	}
}

char	*env_var(t_ms *t, char *str)
{
	int		i;

	i = 0;
	if (str != NULL && *str == '$')
		str++;
	if (str != 0 && *str == '$' && ft_isalpha(*str + 1) == 0)
		return (str);
	while (str != 0 && t->env[i] && \
ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		i++;
	if (str == 0 || ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		return (0);
	else
		return (t->env[i] + ft_strlen(str) + 1);
}

void	get_env(t_ms *t, char **env)
{
	t->env = ft_calloc(1000, sizeof(char *));
	if (*env != 0 || ((env == NULL || *env == 0) && ask_for_env(t) == 0))
	{
		t->i = 0;
		while (env[t->i] != NULL)
		{
			t->env[t->i] = ft_strdup(env[t->i]);
			t->i++;
		}
		t->env[t->i] = NULL;
	}
	env_pars(t);
	get_export(t);
	export_sort(t);
}
