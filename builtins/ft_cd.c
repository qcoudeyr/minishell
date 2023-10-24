/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:04:51 by lheinric          #+#    #+#             */
/*   Updated: 2023/10/24 12:50:27 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gotopath(t_ms *t, char *chemin)
{
	if (chdir(chemin) == 0)
	{
		free(t_pwd);
		t_pwd = chemin;
	}
	else
	{
		pritf("bash: cd: %s: Aucun fichier ou dossier de ce type", chemin);
	}
}

int	ft_cd(t_ms *t, char *path)
{
	char * temppath
	if (path == NULL)
	{
		chdir("~");
		return 1;
	}
	if (path[0] == '/')
		return (gotopath(path));
	else
	{
		temppath = ft_strjoin(t_pwd, "/");
		temppath = ft_strjoin(temppath, path);
		gotopath(temppath);
	}
}

