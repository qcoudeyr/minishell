/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 11:20:25 by  qcoudeyr        ###   ########.fr       */
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
		if (str[i] == 39 && quote == 1)
			quote = 0;
		if (quote == 1 && str[i] == '$')
			i++;
		else if (quote == 0 && str[i] == '$')
			env_var += 1;
		i++;
	}
	return (env_var);
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
	e.newstr = ft_calloc(ft_strlen(str) * 100, sizeof(char));
	e.var = ft_calloc(100000, sizeof(char));
	change_str_env(&e, t, str);
	e.newstr[t->j] = 0;
	free(e.var);
	free(str);
	return (e.newstr);
}
void	change_str_env(t_env e, )

void	hev_quote(char c, int *squote, int *quote)
{
	if (c == 39 && *squote == 0)
		*squote = 1;
	if (c == 34 && *quote == 0)
		*quote = 1;
	if (c == 34 && *quote == 1)
		*quote = 0;
	if (c == 39 && *squote == 1)
		*squote = 0;
}
