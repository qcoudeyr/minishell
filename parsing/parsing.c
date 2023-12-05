/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:40:49 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/05 10:17:55 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(char *str)
{
	if (str != NULL && *str != 0)
	{
		if (access(str, X_OK) != 0)
			return (-1);
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
			t->cmdlist[index][0] = ft_strjoin(t->fpath, (char *) '\0');
		}
		else
			return (ft_cmdnotfound(t, t->cmdlist[index][0]));
		pfree(t->fpath);
	}
	return (0);
}
char **set_env_var()

int	cmdformat(t_ms *t)
{
	int		i;
	int		j;
	void	*tf;

	j = 0;
	i = 0;
	t->cmd[i] = rmcharq(t->cmd[i], '\\');
	if (t->cmd[i] != NULL && *t->cmd[i] != 0)
	{
		if (*t->cmd[i] == 0)
			return (-1);
		tf = (void *) t->cmdlist[i];
		t->cmdlist[i] = ft_splitq(t->cmd[i]);
		free (tf);
		if (have_pipe(t->cmdlist[i]) == 1)
			handle_pipe(t);
		while (t->cmdlist[i][j] != 0)
		{
			t->cmdlist[i][j] = handle_env_var(t, t->cmdlist[i][j]);
			t->cmdlist[i][j] = remove_quotes(t->cmdlist[i][j]);
			j++;
		}
		return (cmd_handler(t));
	}
	return (-1);
}

int	cmd_handler(t_ms *t)
{
	t->i = 0;
	t->return_v = 0;
	while (t->cmdlist[t->i] != NULL)
	{
		t->j = 0;
		if (is_builtins(t->cmdlist[t->i][0]) == 0 && \
is_special(t->cmdlist[t->i][0]) == 0)
			t->return_v = pathfinder(t, t->i);
		while (t->cmdlist[t->i][t->j] != NULL)
		{
			if (*t->cmdlist[t->i][t->j] != 0 && *t->cmdlist[t->i][t->j] == '/')
				t->return_v = check_path(t->cmdlist[t->i][t->j]);
			if (*t->cmdlist[t->i][t->j] != 0 && *t->cmdlist[t->i][t->j] == '$' \
			&& t->cmdlist[t->i][t->j][1] != 0)
			{
				if (*t->cmdlist[t->i][0] == 0)
					t->return_v = -1;
				printf("%s\n", t->cmdlist[t->i][0]);
				t->return_v = -1;
			}
			t->j++;
		}
		t->i++;
	}
	return (t->return_v);
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
