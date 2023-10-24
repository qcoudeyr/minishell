/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/24 09:51:39 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void printenv(char **envp)
{
	int j;

	j = -1;
	while (envp[++j] != NULL)
		printf("%s\n", envp[j]);
}

int	is_builtins(t_ms *t, int i)
{
	int	is_b;

	is_b = 0;
	if (ft_strncmp("env", t->cmd[i], 4) == 0)
	{
		is_b += 1;
		printenv(t->env);
	}
	if (ft_strncmp("clear", t->cmd[i], 5) == 0)
	{
		is_b += 1;
		printf("\033[2J\033[H");
	}
	return (is_b);
}
