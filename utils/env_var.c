/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:31:40 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/21 10:55:19 by  qcoudeyr        ###   ########.fr       */
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
		return 0;
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
	int	i;
	int	j;
	int	quote;
	int	squote;
	int	len;
	char *var;
	char *newstr;

	i = 0;
	j = 0;
	quote = 0;
	squote = 0;
	len = 0;
	if (!str)
		return NULL;
	if (detect_env_var(str) == 0)
		return (str);
	newstr = ft_calloc(ft_strlen(str) * 100, sizeof(char));
	var = ft_calloc(100000, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == 39 && squote == 0)
			squote = 1;
		if (str[i] == 34 && quote == 0)
			quote = 1;
		if (str[i] == 34 && quote == 1)
			quote = 0;
		if (str[i] == 39 && squote == 1)
			squote = 0;
		if ((quote == 1 || (squote == 0 && quote == 0)) && str[i] == '$' && ft_isalpha(str[i+1]))
		{
			while(ft_isalpha(str[++i]) != 0)
				var[len++] = str[i];
			var[len] = 0;
			newstr = ft_strjoin(newstr, env_var(t, var));
			free(var);
			var = ft_calloc(1000, sizeof(char));
			j = ft_strlen(newstr);
		}
		if (str[i] != 0)
			newstr[j++] = str[i++];
	}
	newstr[j] = 0;
	free(var);
	return (newstr);
}
