/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:02:42 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 11:07:21 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*env_var(t_ms *t, char *str)
{
	int		i;

	i = 0;
	if (str != NULL && *str == '$')
		str++;
	if (str != 0 && *str == '$' && ft_isalpha(*str+1) == 0)
		return (str);
	while (str != 0 && t->env[i] && \
ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		i++;
	if (str == 0 || ft_strnstr(t->env[i], str, ft_strlen(str)) == 0)
		return (0);
	else
		return (t->env[i] + ft_strlen(str) + 1);
}
