/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 11:16:21 by  qcoudeyr        ###   ########.fr       */
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

	t->i = 0;
	t->j = 0;
	quote = 0;
	squote = 0;
	len = 0;
	if (!str)
		return (NULL);
	if (detect_env_var(str) == 0)
		return (str);
	newstr = ft_calloc(ft_strlen(str) * 100, sizeof(char));
	var = ft_calloc(100000, sizeof(char));
	while (str[t->i] != '\0')
	{
		hev_quote(str[t->i], &squote, &quote);
		if ((quote == 1 || (squote == 0 && quote == 0)) && str[t->i] == '$' && \
ft_isalpha(str[t->i + 1]))
		{
			while (ft_isalpha(str[++t->i]) != 0)
				var[len++] = str[t->i];
			var[len] = 0;
			newstr = ft_strjoin(newstr, env_var(t, var));
			free(var);
			var = ft_calloc(1000, sizeof(char));
			t->j = ft_strlen(newstr);
		}
		if (str[t->i] != 0)
			newstr[t->j++] = str[t->i++];
	}
	newstr[t->j] = 0;
	free(var);
	free(str);
	return (newstr);
}

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
