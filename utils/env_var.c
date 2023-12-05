/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 09:47:15 by  qcoudeyr        ###   ########.fr       */
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

	i = 0;
	if (str != NULL && ft_strchr(str, '=') == 0)
		return (0);
	else
	{
		while (str[i] != 0)
		{
			if (ft_isal)
			i++;
		}
	}

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
	if (is_set_env_var(str) == 0)
		return (str);
	e.newstr = ft_calloc(ft_strlen(str) * 100, sizeof(char));
	e.var = ft_calloc(100000, sizeof(char));
	change_str_env(&e, t, str);
	free(e.var);
	free(str);
	return (e.newstr);
}

void	change_str_env(t_env *e, t_ms *t, char *str)
{
	while (str[t->i] != '\0')
	{
		hev_quote(str[t->i], &e->squote, &e->quote);
		if ((e->quote == 1 || (e->squote == 0 && e->quote == 0)) && \
	str[t->i] == '$' && ft_isalpha(str[t->i + 1]))
		{
			while (ft_isalpha(str[++t->i]) != 0)
				e->var[e->len++] = str[t->i];
			e->var[e->len] = 0;
			e->newstr = ft_strjoin(e->newstr, env_var(t, e->var));
			free(e->var);
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
