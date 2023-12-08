/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:24:27 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/09 23:54:46 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (c);
	else
		return (0);
}

char	*remove_quotes(char *str)
{
	struct s_henv	s;
	int				j;
	int				i;

	if (!str)
		return (NULL);
	s.len = ft_strlen(str);
	s.newstr = ft_calloc(s.len + 10, sizeof(char));
	if (!s.newstr)
		return (NULL);
	j = 0;
	i = 0;
	while (i < s.len)
	{
		if (is_quote(str[i]) != 0)
		{
			if (s.quote == 0 || s.quote == is_quote(str[i]))
			{
				if (s.quote != 0)
					s.quote = 0;
				else
					s.quote = str[i];
				i++;
			}
			else
				s.newstr[j++] = str[i++];
		}
		else
			s.newstr[j++] = str[i++];
	}
	s.newstr[j] = '\0';
	str = pfree(str);
	return (s.newstr);
}
