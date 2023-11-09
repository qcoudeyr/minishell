/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/09 23:57:36 by lheinric         ###   ########.fr       */
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
	char **cmd;
	char	*cmdone;

	cmd = ft_split(t->cmd[i], ' ');
	cmdone = remove_quotes(cmd[0]);

	is_b = 0;
	if (ft_strncmp("env", cmdone, 4) == 0)
	{
		is_b += 1;
		printenv(t->env);
	}
	if (ft_strncmp("clear", cmdone, 5) == 0)
	{
		is_b += 1;
		printf("\033[2J\033[H");
	}
	if (ft_strncmp("pwd", cmdone, 3) == 0)
	{
		is_b += 1;
		printf("%s\n", t->pwd);
	}
	if (ft_strncmp("echo", cmdone, 4) == 0)
	{
		is_b += 1;
	}
	if (ft_strncmp("cd", cmdone, 3) == 0)
	{
		is_b += 1;
		ft_cd(t, cmdone);
	}
	if (ft_strncmp("help", cmdone, 3) == 0)
	{
		if (ft_strncmp("help cmd", cmdone, 8) == 0)
			print_help(1);
		else
			print_help(0);
		is_b += 1;
	}
	free(cmdone);
	return (is_b);
}
