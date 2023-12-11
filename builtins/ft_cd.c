/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/11 18:14:03 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prevpath(t_ms *t, int n)
{
	int		i;
	char	*newpwd;

	i = ft_strlen(t->pwd);
	while (i > 1 && n > 0)
	{
		i--;
		if (t->pwd[i] == '/')
			n--;
	}
	newpwd = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(newpwd, t->pwd, i + 1);
	return (newpwd);
}

void	remove_prevpath(t_ms *t, t_env *s, char *pth)
{
	while (pth[s->i] != 0)
	{
		while(ft_strncmp(pth + s->i, "../", 3) == 0)
		{
			s->len += 1;
			s->i += 3;
		}
		if (s->len != 0)
		{
			t->temp = prevpath(t, s->len) ;
			t->ptr = s->var;
			s->var= ft_strjoin(s->var, t->temp);
			t->ptr = pfree(t->ptr);
			t->temp = pfree(t->temp);
			s->j = ft_strlen(s->var);
		}
		else
			s->var[s->j] = pth[s->i];
		s->j++;
		s->i++;
	}
	s->var[s->j] = 0;
}

char	*h_ppath(t_ms *t, char *pth)
{
	struct s_henv	s;

	s.len = 0;
	s.var= ft_calloc(ft_strlen(pth) * 3, sizeof(char));
	if (!pth)
		return (pth);
	s.i = 0;
	s.j = 0;
	remove_prevpath(t, &s, pth);
	return (s.var);
}

char	*format_path(char *chemin)
{
	char	*nchr;
	int		i;
	int		j;

	if (!chemin)
		return (chemin);
	nchr = ft_calloc(ft_strlen(chemin) * 2, sizeof(char));
	i = 0;
	j = 0;
	while (chemin[i] != 0)
	{
		nchr[j++] = chemin[i];
		while (ft_strncmp((chemin + i), "//", 2) == 0)
			i++;
		while (nchr[j - 1] == '/' && ft_strncmp((chemin + i +1), "./", 2) == 0)
			i += 2;
		i++;
	}
	nchr[j] = 0;
	chemin = pfree(chemin);
	return (nchr);
}

int	gotopath(char *chemin, t_ms *t)
{
	chemin = h_ppath(t, chemin);
	if (chdir(chemin) == 0)
	{
		change_env(t, "OLDPWD=", t->pwd);
		change_env(t, "PWD=", chemin);
		return (0);
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", chemin);
		return (2);
	}
}

int	gotoprevpath(t_ms *t, char *chemin)
{
/* 	int		i;
	int		j; */
	char	*newpwd;

	newpwd = h_ppath(t, chemin);
	if (chdir(newpwd) == 0)
	{
		change_env(t, "OLDPWD=", t->pwd);
		change_env(t, "PWD=", newpwd);
		newpwd = pfree(newpwd);
		return (0);
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", newpwd);
		newpwd = pfree(newpwd);
	}
	return (2);
}

int	ft_cd(t_ms *t, char **path)
{
	char *tpath;

	t->i = 1;
	if (path[t->i] == NULL || path[t->i][0] == '~' || path[t->i][0] == '\0')
		t->return_v = gotopath(t->home, t);
	while (path[t->i] != NULL )
	{
		if (path[t->i][0] == '/')
			t->return_v = gotopath(path[t->i], t);
		else if (ft_strncmp(path[t->i], "../", 3) == 0 || ft_strcmp(path[t->i], "..") == 0)
			t->return_v = gotoprevpath(t, path[t->i]);
		else if (ft_strcmp(path[t->i], ".") == 0 || ft_strcmp(path[t->i], "./") == 0 )
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
