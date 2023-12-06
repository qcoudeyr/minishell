/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 13:47:19 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detect_env_var(char *str)
{
	int	i;
	int	quote;
	int	env_var;

	i = 0;
	quote = 0;
	env_var = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == 39 && quote == 0)
			quote = 1;
		else if (str[i] == 39 && quote == 1)
			quote = 0;
		if (quote == 1 && str[i] == '$')
			i++;
		else if (quote == 0 && str[i] == '$')
			env_var += 1;
		i++;
	}
	return (env_var);
}

int	is_set_env_var(char *str)
{
	int	i;
	int	have_equal;

	i = 0;
	have_equal = 0;
	if (str != NULL && ft_strchr(str, '=') == 0)
		return (0);
	else
	{
		while (str[i] != 0)
		{
			if (ft_isalpha(str[i]) == 0 && ft_isalnum(str[i]) == 0)
			{
				if (str[i] != '=' && str[i + 1] != 0)
					return (0);
				else if (str[i] == '=' && str[i + 1] != 0)
					have_equal = 1;
			}
			i++;
		}
		if (have_equal == 1 && str[i - 1] != '=')
			return (1);
	}
	return (0);
}

char	*handle_env_var(t_ms *t, char *str)
{
	struct s_henv	e;

	t->i = 0;
	t->j = 0;
	e.quote = 0;
	e.squote = 0;
	e.len = 0;
	if (!str)
		return (NULL);
	if (detect_env_var(str) == 0)
		return (str);
	if (ft_strncmp(str, "$?", 3) == 0)
		e.newstr = ft_itoa(t->status >> 8);
	else
	{
		e.newstr = ft_calloc((ft_strlen(str) * 10), sizeof(char));
		e.var = ft_calloc(1000, sizeof(char));
		change_str_env(&e, t, str);
		e.var = pfree(e.var);
	}
	str = pfree(str);
	return (e.newstr);
}

void	change_str_env(t_env *e, t_ms *t, char *str)
{
	while (str[t->i] != '\0')
	{
		e->len = 0;
		hev_quote(str[t->i], &e->squote, &e->quote);
		if ((e->quote == 1 || (e->squote == 0 && e->quote == 0)) && \
	str[t->i] == '$' && ft_isalpha(str[t->i + 1]))
		{
			while (ft_isalpha(str[++t->i]) != 0)
				e->var[e->len++] = str[t->i];
			e->var[e->len] = 0;
			ft_strlcpy(e->newstr + t->j, env_var(t, e->var), ft_strlen(env_var(t, e->var)) + 1);
			e->var = pfree(e->var);
			e->var = ft_calloc(1000, sizeof(char));
			t->j = ft_strlen(e->newstr);
		}
		if (str[t->i] != 0)
			e->newstr[t->j++] = str[t->i++];
	}
	e->newstr[t->j] = 0;
}

void	hev_quote(char c, int *squote, int *quote)
{
	if ((c == 34 && *quote == 1) || (c == 39 && *squote == 1))
	{
		if (c == 34 && *quote == 1)
			*quote = 0;
		if (c == 39 && *squote == 1)
			*squote = 0;
	}
	else if ((c == 34 && *quote == 0) || (c == 39 && *squote == 0))
	{
		if (c == 39 && *squote == 0)
			*squote = 1;
		if (c == 34 && *quote == 0)
			*quote = 1;
	}
}
