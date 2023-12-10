/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:01 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/10 19:23:39 by  qcoudeyr        ###   ########.fr       */
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

int	check_temp(t_ms *t, char *temp, int index)
{
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

int	check_redirect_error(t_ms *t, int index)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	t->temp = NULL;
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


	return (check_temp(t, temp, index));
}

int	h_nalhpa(t_ms *t, char **lst)
{
	if (lst != NULL && *lst != NULL && ft_strchr("<>|&", lst[0][0]) != NULL && t->status == 0)
	{
		t->temp = ft_strjoin(\
"minishell : syntax error near unexpected token \'", &lst[0][0]);
		write(0, t->temp, ft_strlen(t->temp));
		write(0, "\'\n", 2);
		t->temp = pfree(t->temp);
		t->status = 512;
		return (2);
	}
	else if (t->status != 0)
			return (2);
	return (0);
}
