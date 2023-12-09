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

void	*init_rq(t_env *s, char *str)
{
	s->len = ft_strlen(str);
	s->newstr = ft_calloc(s->len + 10, sizeof(char));
	if (!s->newstr)
		return (NULL);
	s->j = 0;
	s->i = 0;
	s->quote = 0 ;
	return (str);
}

char	*remove_quotes(char *str)
{
	struct s_henv	s;

	if (init_rq(&s, str) == NULL)
		return (NULL);
	while (s.i < s.len)
	{
		if (is_quote(str[s.i]) != 0)
		{
			if (s.quote == 0 || s.quote == is_quote(str[s.i]))
			{
				if (s.quote != 0)
					s.quote = 0;
				else
					s.quote = str[s.i];
				s.i++;
			}
			else
				s.newstr[s.j++] = str[s.i++];
		}
		else
			s.newstr[s.j++] = str[s.i++];
	}
	s.newstr[s.j] = '\0';
	str = pfree(str);
	return (s.newstr);
}
