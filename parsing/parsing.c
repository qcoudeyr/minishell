/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:40:49 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/17 11:13:19 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pathfinder(t_ms *t, int index)
{
	int	i;

	if (t->path == NULL && is_builtins(t->cmdl[index][0]) == 0)
		return (ft_cmdnotfound(t, t->cmdl[index][0]));
	if (t->cmdl[index][0] != NULL && *t->cmdl[index][0] != 0)
	{
		i = 0;
		if (check_access(t->cmdl[index][0]) == 0)
			return (0);
		t->fpath = ft_strjoin(t->path[i], t->cmdl[index][0]);
		while (access (t->fpath, X_OK) < 0 && t->path[i + 1] != NULL)
		{
			t->fpath = pfree(t->fpath);
			t->fpath = ft_strjoin(t->path[i++], t->cmdl[index][0]);
		}
		if (access(t->fpath, X_OK) == 0)
			change_path(t, index);
		else
		{
			t->fpath = pfree(t->fpath);
			return (ft_cmdnotfound(t, t->cmdl[index][0]));
		}
	}
	return (0);
}

char	*spec_format(char *str)
{
	struct s_henv	s;

	s.i = 0;
	s.j = 0;
	s.quote = 0;
	if (!str || *str == 0)
		return (str);
	s.newstr = ft_calloc((ft_strlen(str) + 1) * 2, sizeof(char));
	while (str[s.i] != 0)
	{
		if (str[s.i] == '\'' || str[s.i] == '"')
			s.quote += 1;
		if (ft_strchr("|<>&", str[s.i]) != NULL && (s.quote % 2) == 0)
		{
			s.newstr[s.j++] = ' ';
			while (str[s.i] != 0 && ft_strchr("|<>&", str[s.i]) != NULL)
				s.newstr[s.j++] = str[s.i++];
			s.newstr[s.j++] = ' ';
		}
		else
			s.newstr[s.j++] = str[s.i++];
	}
	s.newstr[s.j] = 0;
	str = pfree(str);
	return (s.newstr);
}

int	cmdformat(t_ms *t)
{
	int		i;
	int		j;

	i = 0;
	first_format(t);
	if (t->cmd[t->nc] != NULL && *t->cmd[t->nc] != 0 && check_cmd_err(t) == 0)
	{
		if (*t->cmd[t->nc] == 0)
			return (-1);
		t->temp = (void *) t->cmdl[i];
		t->cmdl[i] = ft_splitq(t->cmd[t->nc]);
		t->cmdl[i + 1] = NULL;
		t->temp = pfree(t->temp);
		if (have_meta(t->cmdl[i]) == 1)
			handle_m(t);
		while (t->cmdl[i] != NULL)
		{
			j = -1;
			while (t->cmdl[i][++j] != NULL)
				t->cmdl[i][j] = remove_quotes(handle_env_var(t, t->cmdl[i][j]));
			i++;
		}
		return (cmd_handler(t));
	}
	return (-1);
}

int	cmd_handler(t_ms *t)
{
	int	rv;

	t->i = 0;
	rv = 0;
	while (t->cmdl[t->i] != NULL)
	{
		t->j = 0;
		if (is_builtins(t->cmdl[t->i][0]) == 0 && \
is_spec(t->cmdl[t->i][0]) == 0)
			rv = pathfinder(t, t->i);
		while (t->cmdl[t->i][t->j] != NULL)
		{
			if (*t->cmdl[t->i][t->j] && *t->cmdl[t->i][t->j] == '/' && rv == 0)
				rv = check_path(t);
			if (rv < 0 && is_or(t->cmdl[t->i][t->j]) == 1)
				rv = 0;
			t->j++;
		}
		t->i++;
	}
	return (rv);
}

char	*rmcharq(char *str, char c)
{
	int		i;
	int		j;
	int		quote;
	char	*temp;

	i = 0;
	j = 0;
	quote = 0;
	if (!str || *str == 0)
		return (str);
	temp = ft_calloc(ft_strlen(str) + 2, sizeof(char));
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
	str = pfree(str);
	return (temp);
}
