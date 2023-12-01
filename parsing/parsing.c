/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:40:49 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/01 21:15:23 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(char *str)
{
	if (str != NULL && *str != 0)
	{
		if (access(str, X_OK) != 0)
			return(-1);
	}
	return (0);
}

int	pathfinder(t_ms *t, int index)
{
	int	i;

	if (t->cmdlist[index][0] != NULL && *t->cmdlist[index][0] != 0)
	{
		i = 0;
		if (check_path(t->cmdlist[index][0]) == 0)
			return (0);
		t->fpath = ft_strjoin(t->path[i], t->cmdlist[index][0]);
		while (access (t->fpath, X_OK) < 0 && t->path[i + 1] != NULL)
		{
			pfree(t->fpath);
			t->fpath = ft_strjoin(t->path[i++], t->cmdlist[index][0]);
		}
		if (access(t->fpath, X_OK) == 0)
		{
			pfree(t->cmdlist[index][0]);
			t->cmdlist[index][0] = ft_strjoin(t->fpath, (char *)'\0');
		}
		else
			return(ft_cmdnotfound(t, t->cmdlist[index][0]));
		pfree(t->fpath);
	}
	return (0);
}

char	*env_var(t_ms *t, char *str)
{
	int		i;

	i = 0;
	if (str != NULL && *str == '$')
		str++;
	if (str != 0 && *str == '$' && ft_isalpha(*str+1) == 0)
		return (str);
	while (str != 0 && t->env[i] &&ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		i++;
	if (str == 0 || ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		return (0);
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
	int		j;
	void	*tf;

	j = 0;
	i = 0;
	t->cmdlist[i] = NULL;
	t->cmd[i] = rmcharq(t->cmd[i], '\\');
	if (t->cmd[i] != NULL && *t->cmd[i] != 0)
	{
		if (*t->cmd[i] == 0)
			return (-1);
		tf = (void *) t->cmdlist[i];
		t->cmdlist[i] = ft_splitq(t->cmd[i]);
		free (tf);
		while ( t->cmdlist[i][j] != 0)
		{
			t->cmdlist[i][j] = handle_env_var(t, t->cmdlist[i][j]);
			t->cmdlist[i][j] = remove_quotes(t->cmdlist[i][j]);
			j++;
		}
		if (have_pipe(t->cmdlist[i]) == 1)
			handle_pipe(t);
		return (cmd_handler(t));
	}
	return (-1);
}

int	cmd_handler(t_ms *t)
{
	int	i;
	int	j;
	int	return_v;

	i = 0;
	return_v = 0;
	while (t->cmdlist[i] != NULL)
	{
		j = 0;
		if (is_builtins(t->cmdlist[i][0]) == 0 && is_special(t->cmdlist[i][0]) == 0)
			return_v = pathfinder(t, i);
		while (t->cmdlist[i][j] != NULL)
		{
			if (*t->cmdlist[i][j] != 0 && *t->cmdlist[i][j] == '/')
				return_v = check_path(t->cmdlist[i][j]);
			if (*t->cmdlist[i][j] != 0  && t->cmdlist[i][j][1] != 0 && *t->cmdlist[i][j] == '$')
			{
				if (*t->cmdlist[i][0] == 0)
					return_v = -1;
				printf("%s\n", t->cmdlist[i][0]);
				return_v = -1;
			}
			j++;
		}
		i++;
	}
	return(return_v);
}

int	is_special(char *str)
{
	if (str != NULL && (*str == '|' || *str == '&'))
		return (1);
	else
		return (0);
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

char	*rmcharq(char *str, char c)
{
	int	i;
	int j;
	int	quote;
	char *temp;

	i = 0;
	j = 0;
	quote = 0;
	temp = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	if (!str || *str == 0)
		return (str);
	while (str[i] == ' ')
		i++;
	while (str[i] != 0)
	{
		if (str[i] == '\'' || str[i] == '"')
			quote += 1;
		if (str[i] == c && quote == 0)
			i++;
		else
			temp[j++] = str[i++];
	}
	temp[j] = 0;
	free(str);
	return (temp);
}
