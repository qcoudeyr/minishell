/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:12:29 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/13 18:13:01 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_prevpath(t_ms *t, t_env *s, char *pth)
{
	while (pth[s->i] != 0)
	{
		if (ft_strrchr("\'\"", pth[s->i]))
			s->quote += 1;
		if (s->quote == 2)
			s->quote = 0;
		check_relative_path(t, s, pth);
		check_relative_spath(t, s, pth);
		if (pth[s->i] == '~' && s->i > 0 && pth[s->i - 1] != '/' && !s->quote)
		{
			s->var = ft_strjoin(s->var, t->home);
			s->j = ft_strlen(s->var);
			s->i++;
		}
		if (pth[s->i] == '/' && pth[s->i + 1] == 0 && s->len < 0)
		{
			s->j++;
			s->i++;
		}
		else
			s->var[s->j++] = pth[s->i++];
	}
	s->var[s->j] = 0;
}
