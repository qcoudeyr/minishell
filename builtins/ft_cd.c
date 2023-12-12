/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/12 11:29:41 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*h_rpath(t_ms *t, char *pth)
{
	struct s_henv	s;

	s.len = 0;
	s.var = ft_calloc(ft_strlen(pth) * 3, sizeof(char));
	if (!pth)
		return (pth);
	s.i = 0;
	s.j = 0;
	remove_prevpath(t, &s, pth);
	pth = pfree(pth);
	return (format_path(s.var));
}

int	gotopath(char *chemin, t_ms *t)
{
	if (chdir(chemin) == 0)
	{
		change_env(t, "OLDPWD=", t->pwd);
		change_env(t, "PWD=", chemin);
		return (0);
	}
	else
	{
		ft_printf("minishell: cd: %s: Aucun fichier ou dossier de ce type\n", \
chemin);
		return (2);
	}
}

int	ft_cd(t_ms *t, char **path)
{
	char	*tpath;

	t->i = 1;
	if (path[t->i] == NULL || path[t->i][0] == '~' || path[t->i][0] == '\0')
		t->return_v = gotopath(t->home, t) - (0 * t->i++);
	while (path[t->i] != NULL)
	{
		if (path[t->i][0] == '/')
			t->return_v = gotopath(path[t->i], t);
		else if (!ft_strcmp(path[t->i], ".") || !ft_strcmp(path[t->i], "./"))
			t->return_v = 0;
		else if (path[t->i][0] != '\0')
		{
			tpath = ft_strjoin(t->pwd, "/");
			t->temp = tpath;
			tpath = ft_strjoin(t->temp, path[t->i]);
			t->temp = pfree(t->temp);
			t->return_v = gotopath(tpath, t);
			tpath = pfree(tpath);
		}
		t->i++;
	}
	return (t->return_v);
}
