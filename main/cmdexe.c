/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/06 10:55:06 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_help(int i)
{
	int		fd;
	char	*str;

	if (i == 1)
		fd = open("./main/cmd", O_RDONLY);
	else
		fd = open("./main/help", O_RDONLY);
	if (fd == -1)
		return (-1);
	str = get_next_line(fd);
	while(str != NULL)
	{
		printf("%s",str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (0);
}

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
	if (ft_strncmp("pwd", t->cmd[i], 3) == 0)
	{
		is_b += 1;
		printf("%s\n", t->pwd);
	}
	if (ft_strncmp("echo", t->cmd[i], 3) == 0)
	{
		is_b += 1;
		
	}
	if (ft_strncmp("help", t->cmd[i], 3) == 0)
	{
		if (ft_strncmp("help cmd", t->cmd[i], 8) == 0)
			print_help(1);
		else
			print_help(0);
		is_b += 1;
	}
	return (is_b);
}
