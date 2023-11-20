/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:40:49 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/20 10:28:13 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pathfinder(t_ms *t)
{
	int	i;
	int	arg;

	arg = 0;
	if (t->cmdlist[arg][0] != NULL && *t->cmdlist[arg][0] != 0)
	{
		i = 0;
		t->fpath = ft_strjoin(t->path[i], t->cmdlist[arg][0]);
		while (access (t->fpath, X_OK) < 0 && t->path[i + 1] != NULL)
		{
			free(t->fpath);
			t->fpath = ft_strjoin(t->path[i++], t->cmdlist[arg][0]);
		}
		if (access(t->fpath, X_OK) == 0)
		{
			if (t->cmdlist[arg][0] != NULL)
				free(t->cmdlist[arg][0]);
			t->cmdlist[arg][0] = ft_strdup(t->fpath);
		}
		else
			return(ft_cmdnotfound(t, t->cmdlist[arg][0]));
		arg++;
		free(t->fpath);
		t->fpath = NULL;
	}
	return (0);
}

char	*env_var(t_ms *t, char *str)
{
	int		i;

	i = 0;
	while (ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		i++;
	if (ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		return (NULL);
	else
		return (t->env[i] + ft_strlen(str) + 1);
}


void	env_var_detect(t_ms *t)
{
	int		i;
	char	*tmp;

	i = 0;
	while (t->cmdlist[0][i] != NULL)
	{
		if (ft_strnstr(t->cmdlist[0][i], "$", 1) != 0)
		{
			tmp = env_var(t, t->cmdlist[0][i]);
			if (tmp != NULL)
				t->cmdlist[0][i] = tmp;
		}
		i++;
	}
}

int	cmdformat(t_ms *t)
{
	int		i;

	i = 0;
	t->cmdlist = ft_calloc(2 , sizeof(char **));
	t->cmdlist[i] = NULL;
	if (t->cmd[i] != NULL && *t->cmd[i] != 0)
	{
		t->cmdlist[i] = ft_splitq(t->cmd[i]);
		for (int j = 0; t->cmdlist[i][j] != 0; j++)
			t->cmdlist[i][j] = remove_quotes(t->cmdlist[i][j]);
		env_var_detect(t);
		return (pathfinder(t));
	}
	return (-1);
}

void	env_pars(t_ms *t)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strnstr(t->env[i], "PATH=", 5) == 0)
		i++;
	t->path = ft_split((t->env[i] + 5), ':');
	i = 0;
	while (ft_strnstr(t->env[i], "PWD=", 4) == 0)
		i++;
	t->pwd = ft_strdup(t->env[i] + 4);
	i = 0;
	while (ft_strnstr(t->env[i], "HOME=", 5) == 0)
		i++;
	t->home = ft_strdup(t->env[i] + 5);
	i = 0;
	while (t->path[i])
	{
		temp = ft_strdup(t->path[i]);
		free(t->path[i]);
		t->path[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}
