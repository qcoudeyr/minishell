/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:50:52 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/17 11:53:10 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sf_rplc(char *str, char *toreplace)
{
	if (str != NULL)
		str = pfree(str);
	str = ft_strdup(toreplace);
	if (toreplace != NULL)
		toreplace = pfree(toreplace);
	return (str);
}

int	is_vname(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (!ft_isalpha(str[i]) && !ft_strchr("_./", str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && !ft_strchr("_-./", str[i]))
			return (0);
		i++;
	}
	if (str[i] == 0)
		return (1);
	else
		return (0);
}

void	hev_quote(char c, int *squote, int *quote, int *fquote)
{
	if ((*quote == 0) && (*squote == 0))
		*fquote = c;
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
