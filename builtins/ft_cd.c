/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/11 12:21:48 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", chemin);
		return (2);
	}
}

int	gotoprevpath(t_ms *t)
{
	int		i;
	int		j;
	char	*newpwd;

	j = -1;
	i = ft_strlen(t->pwd);
	while (t->pwd[i] != '/' && i > 1)
		i--;
	newpwd = ft_calloc((i + 1), sizeof(char));
	while (++j < i)
		newpwd[j] = t->pwd[j];
	newpwd[j] = '\0';
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
	char	*temppath;

	if (path[1] == NULL || path[1][0] == '~' || path[1][0] == '\0')
		t->return_v = gotopath(t->home, t);
	else if (path[1][0] == '/')
		t->return_v = gotopath(path[1], t);
	else if (path[1][0] == '.' && path[1][1] == '.' && path[1][2] == '\0')
		t->return_v = gotoprevpath(t);
	else if (path[1][0] == '.' && path[1][1] == '\0')
		t->return_v = 0;
	else if (path[1][0] != '\0')
	{
		temppath = ft_strjoin(t->pwd, "/");
		t->temp = temppath;
		temppath = ft_strjoin(temppath, path[1]);
		t->temp = pfree(t->temp);
		t->return_v = gotopath(temppath, t);
		temppath = pfree(temppath);
	}
	return (t->return_v);
}
