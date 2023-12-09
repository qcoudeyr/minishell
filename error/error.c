/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/09 13:00:04 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmdnotfound(t_ms *t, char *str)
{
	(void) t;
	if (check_access(str) != 0 && is_builtins(str) == 0)
	{
		printf("Command not found: %s\n", str);
		t->status = 32512;
	}
	return (-1);
}

void	ft_acceserror(t_ms *t)
{
	if (errno == ENOENT)
		ft_printf("Input file does not exist.\n");
	else if (errno == EACCES)
		ft_printf("Input file is not readable or permission denied.\n");
	else
		ft_perror(t, "access");
	exit(EXIT_FAILURE);
}

int	check_redirect_error(t_ms *t, int index)
{
	int		i;
	char	*temp;

	i = 0;
	temp = pfree(t->temp);
	while (t->cmdl[index] != NULL && t->cmdl[index][i] != NULL)
	{
		if (t->cmdl[index][i][0] == '<' && t->cmdl[index][i + 1] != NULL)
			t->temp = t->cmdl[index][i + 1];
		else if (ft_strchr(t->cmdl[index][i], '>') != 0 && \
	t->cmdl[index][i + 1] != NULL)
			temp = t->cmdl[index][i + 1];
		if (temp != NULL && t->temp != NULL)
			break ;
		i++;
	}
	if (temp && t->temp && ft_strcmp(temp, t->temp) == 0)
	{
		temp = ft_strjoin(t->cmdl[index][0], ": input file is output file\n");
		write(0, temp, ft_strlen(temp));
		temp = pfree(temp);
		t->status = 512;
		return (-1);
	}
	return (0);
}
