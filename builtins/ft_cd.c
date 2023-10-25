/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/10/24 13:56:46 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gotopath(t_ms *t, char *chemin)
{
	if (chdir(chemin) == 0)
	{
		free(t->pwd);
		t->pwd = chemin;
		return 1;
	}
	else
	{
		printf("bash: cd: %s: Aucun fichier ou dossier de ce type", chemin);
		return 0;
	}
}

int	ft_cd(t_ms *t, char *path)
{
	char * temppath;

	if (path == NULL)
	{
		chdir("/~");
		return 1;
	}
	if (path[0] == '/')
		return (gotopath(path, t));
	else
	{
		temppath = ft_strjoin(t->pwd, "/");
		temppath = ft_strjoin(temppath, path);
		gotopath(temppath, t);
		return (1);
	}
}