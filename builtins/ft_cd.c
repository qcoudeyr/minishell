/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/05 19:17:28 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gotopath(char *chemin, t_ms *t)
{
	if (chdir(chemin) == 0)
	{
		t->pwd = pfree(t->pwd);
		t->pwd = ft_strdup(chemin);
		return (1);
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", chemin);
		return (0);
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
	newpwd = malloc(sizeof(char) * (i + 1));
	while (++j < i)
		newpwd[j] = t->pwd[j];
	newpwd[j] = '\0';
	if (chdir(newpwd) == 0)
	{
		t->pwd = pfree(t->pwd);
		t->pwd = newpwd;
		return (0);
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type\n", newpwd);
		newpwd = pfree(newpwd);
		return (2);
	}
	return (2);
}

int	ft_cd(t_ms *t, char *cmd)
{
	char	*temppath;
	char	**path;

	cmd = *t->cmd;
	path = ft_split(cmd, ' ');
	if (path[1] == NULL || path[1][0] == '~' || path[1][0] == '\0')
		gotopath(t->home, t);
	else if (path[1][0] == '/')
		return (gotopath(path[1], t));
	else if (path[1][0] == '.' && path[1][1] == '.' && path[1][2] == '\0')
		gotoprevpath(t);
	else if (path[1][0] == '.' && path[1][1] == '\0')
		return (1);
	else if (path[1][0] != '\0')
	{
		temppath = ft_strjoin(t->pwd, "/");
		temppath = ft_strjoin(temppath, path[1]);
		gotopath(temppath, t);
	}
	free_tabstr(path);
	return (1);
}
