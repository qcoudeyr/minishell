/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/20 14:52:18 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_env(t_ms *t, char *var, char *tochange)
{
	int		i;
	i = 0;

	while (ft_strnstr(t->env[i], var, ft_strlen(var)) == 0)
		i++;
	if (ft_strnstr(t->env[i], var, ft_strlen(var)) == 0)
		return (-1);
	t->env[i] = ft_strjoin(var, tochange);
	return (0);

}

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
	if (ft_strncmp("env", t->cmdlist[i][0], 4) == 0)
	{
		is_b += 1;
		printenv(t->env);
	}
	if (ft_strncmp("clear", t->cmdlist[0][0], 5) == 0)
	{
		is_b += 1;
		printf("\033[2J\033[H");
	}
	if (ft_strncmp("pwd", t->cmdlist[0][0], 3) == 0)
	{
		is_b += 1;
		printf("%s\n", t->pwd);
	}
	if (ft_strncmp("echo", t->cmdlist[0][0], 4) == 0)
	{
		is_b += 1;
		ft_echo(t->cmdlist[0]);
	}
	if (ft_strncmp("cd", t->cmdlist[0][0], 3) == 0)
	{
		is_b += 1;
		ft_cd(t, t->cmdlist[0][0]);
	}
	if (ft_strncmp("help", t->cmdlist[0][0], 4) == 0)
	{
		if (t->cmdlist[0][1] && ft_strncmp("cmd", t->cmdlist[0][1], 4) == 0)
			print_help(1);
		else
			print_help(0);
		is_b += 1;
	}
	return (is_b);
}
