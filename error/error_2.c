/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:52:11 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/10 19:36:47 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_perror(t_ms *t, char *s)
{
	if (s != NULL)
		perror(s);
	t->return_v = 2;
	return (-1);
}

int	check_cmd_err(t_ms *t)
{
	int	len;

	len = ft_strlen(t->cmd[t->nc]);
	if (len == 0)
		return (2);
	if (len == 1 && ft_strchr("<>|&\'\"\\", t->cmd[t->nc][0]) != NULL)
	{
		t->temp = ft_strjoin(\
"minishell : syntax error near unexpected token \'", &t->cmd[t->nc][0]);
		write(0, t->temp, ft_strlen(t->temp));
		write(0, "\'\n", 2);
		t->temp = pfree(t->temp);
		t->status = 512;
		return (2);
	}
	return (0);
}
