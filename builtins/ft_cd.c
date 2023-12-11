/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/12/11 13:51:30 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*format_path(char *chemin)
{
	char	*nchr;
	int		i;
	int		j;

	if (!chemin)
		return (chemin);
	nchr = ft_calloc(ft_strlen(chemin), sizeof(char));
	i = 0;
	j = 0;
	while (chemin[i] != 0)
	{
		nchr[j++] = chemin[i];
		while(chemin[i] && chemin[i] == '/')
			i++;
	}
	nchr[j] = 0;
	chemin = pfree(chemin);
	return (nchr);
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
	t->i = 1;
	if (path[t->i] == NULL || path[t->i][0] == '~' || path[t->i][0] == '\0')
		t->return_v = gotopath(t->home, t);
	while (path[t->i] != NULL )
	{
		if (path[t->i][0] == '/')
			t->return_v = gotopath(path[t->i], t);
		else if (ft_strcmp(path[t->i], "../") == 0 || ft_strcmp(path[t->i], "..") == 0)
			t->return_v = gotoprevpath(t);
		else if (ft_strcmp(path[t->i], ".") == 0)
			t->return_v = 0;
		else if (path[t->i][0] != '\0')
		{
			t->temp = ft_strjoin(t->pwd, "/");
			t->temp = t->temp;
			t->temp = ft_strjoin(t->temp, path[t->i]);
			t->temp = pfree(t->temp);
			t->return_v = gotopath(t->temp, t);
			t->temp = pfree(t->temp);
		}
		t->i++;
	}
	return (t->return_v);
}
