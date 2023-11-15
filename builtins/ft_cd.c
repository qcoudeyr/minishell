/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/15 10:43:47 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int gotoprevpath(t_ms *t)
{
	int i;
	int j;
	char *newpwd;

	j = -1;
	i = ft_strlen(t->pwd);
	while (t->pwd[i] != '/')
		i--;
	newpwd = malloc(sizeof(char) * (i + 1));
	while (++j < i)
		newpwd[j] = t->pwd[j];
	newpwd[j] = '\0';
	change_env(t, "OLDPWD=", t->pwd);
	free(t->pwd);
	t->pwd = newpwd;
	change_env(t, "PWD=", t->pwd);
	return (1);
}

int	gotopath(char *chemin, t_ms *t)
{
	if (chdir(chemin) == 0)
	{
		change_env(t, "OLDPWD=", t->pwd);
		free(t->pwd);
		t->pwd = chemin;
		change_env(t, "PWD=", t->pwd);
		return 1;
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", chemin);
		return 0;
	}
}

int	ft_cd(t_ms *t, char *cmd)
{
	char *temppath;
	char **path;

	cmd = *t->cmd;
	path = ft_split(cmd, ' ');
	if (path[1] == NULL || path[1][0] == '~' || path[1][0] == '\0')
		gotopath(t->home, t);
	else if (path[1][0] == '/')
		return (gotopath(path[1], t));
	else if	(path[1][0] == '.' && path[1][1] == '.' && path[1][2] == '\0')
		gotoprevpath(t);
	else if (path[1][0] == '.' && path[1][1] == '\0')
		return (1);
	else if (path[1][0] != '\0')
	{
		temppath = ft_strjoin(t->pwd, "/");
		temppath = ft_strjoin(temppath, path[1]);
		gotopath(temppath, t);
	}
	return (1);
}
