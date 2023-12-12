/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:57:13 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/12 19:49:05 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_path(t_ms *t)
{
	if (t->cmdl[t->i][t->j] != NULL && *t->cmdl[t->i][t->j] == '/' && \
ft_strnstr(t->cmdl[t->i][0], "echo", 5) == 0)
	{
		if (access(t->cmdl[t->i][t->j], X_OK) != 0)
		{
			ft_printf("minishell: %s: No such file or directory: %s\n", \
	t->cmdl[t->i][0], t->cmdl[t->i][t->j]);
			return (-1);
		}
	}
	return (0);
}

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
	newpwd = ft_calloc(i * 3, sizeof(char));
	ft_strlcpy(newpwd, t->pwd, i + 1);
	return (newpwd);
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

void	check_relative_path(t_ms *t, t_env *s, char *pth)
{
	while ((!ft_strncmp(pth + s->i, "../", 3) || \
	!ft_strncmp(pth + s->i, "..", 3)) && !s->quote)
	{
		if (s->len < 0)
			s->len = 0;
		if (s->i > 0 && pth[s->i - 1] != '/')
			s->len += 1;
		s->i += 2;
	}
	if (s->len > 0)
	{
		t->temp = prevpath(t, s->len);
		t->ptr = s->var;
		s->var = ft_strjoin(s->var, t->temp);
		t->ptr = pfree(t->ptr);
		t->temp = pfree(t->temp);
		s->j = ft_strlen(s->var);
		s->len = -1;
	}
}

void	check_relative_spath(t_ms *t, t_env *s, char *pth)
{
	while ((!ft_strncmp(pth + s->i, "./", 2) || \
	!ft_strncmp(pth + s->i, ".", 2)) && !s->quote)
	{
		s->i++;
		s->len = 1;
	}
	if (s->len > 0)
	{
		t->temp = ft_strdup(t->pwd);
		t->ptr = s->var;
		s->var = ft_strjoin(s->var, t->temp);
		t->ptr = pfree(t->ptr);
		t->temp = pfree(t->temp);
		s->j = ft_strlen(s->var);
		s->len = -1;
	}
}

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
