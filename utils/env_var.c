/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/17 11:53:57 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	detect_env_var(char *str)
{
	struct s_henv	s;

	s.i = 0;
	s.quote = 0;
	s.fquote = 0;
	s.env_var = 0;
	if (!str)
		return (0);
	while (str[s.i] != '\0')
	{
		if ((str[s.i] == 39 || str[s.i] == '"') && s.fquote == 0)
			s.fquote = str[s.i];
		else if (s.fquote != 0 && str[s.i] == s.fquote)
			s.fquote = 0;
		if (str[s.i] == 39 && s.quote == 0)
			s.quote = 1;
		else if (str[s.i] == 39 && s.quote == 1)
			s.quote = 0;
		if (s.quote == 1 && str[s.i] == '$' && s.fquote != '\"')
			s.i++;
		else if ((s.quote == 0 || s.fquote == '"') && str[s.i] == '$')
			s.env_var += 1;
		s.i++;
	}
	return (s.env_var);
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
		e.newstr = ft_itoa(t->return_v);
	else
	{
		e.newstr = ft_calloc(((ft_strlen(str) + 1) * 100), sizeof(char));
		e.var = ft_calloc(1000, sizeof(char));
		change_str_env(&e, t, str);
		e.var = pfree(e.var);
	}
	str = pfree(str);
	return (e.newstr);
}

void	env_var_returnv(t_env *e, t_ms *t)
{
	e->var = pfree(e->var);
	e->var = ft_itoa(t->return_v);
	ft_strlcpy(e->newstr + t->j, e->var, ft_strlen(e->var) + 1);
	e->var = pfree(e->var);
	e->var = ft_calloc(1000, sizeof(char));
	t->i += 2;
}

void	change_str_env(t_env *e, t_ms *t, char *str)
{
	while (str[t->i] != '\0')
	{
		e->len = 0;
		hev_quote(str[t->i], &e->squote, &e->quote, &e->fquote);
		if ((e->quote == 1 || (e->squote == 0 && e->quote == 0) || \
	e->fquote == '"') && str[t->i] == '$' && ft_isalpha(str[t->i + 1]))
		{
			while (ft_isalpha(str[++t->i]) != 0)
				e->var[e->len++] = str[t->i];
			e->var[e->len] = 0;
			ft_strlcpy(e->newstr + t->j, env_var(t, e->var), \
			ft_strlen(env_var(t, e->var)) + 1);
			e->var = pfree(e->var);
			e->var = ft_calloc(1000, sizeof(char));
		}
		else if ((e->quote == 1 || (e->squote == 0 && e->quote == 0) || \
	e->fquote == '"') && str[t->i] == '$' && str[t->i + 1] == '?')
			env_var_returnv(e, t);
		t->j = ft_strlen(e->newstr);
		if (str[t->i] != 0)
			e->newstr[t->j++] = str[t->i++];
	}
	e->newstr[t->j] = 0;
}
