/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/06 09:27:38 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_env(t_ms *t, char *var, char *tochange)
{
	void	*ptr;
	int		i;

	i = 0;
	while (ft_strnstr(t->env[i], var, ft_strlen(var)) == 0)
		i++;
	if (ft_strnstr(t->env[i], var, ft_strlen(var)) == 0)
		return (-1);
	ptr = t->env[i];
	t->env[i] = ft_strjoin(var, tochange);
	ptr = pfree(ptr);
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
	while (str != NULL)
	{
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (0);
}

int	printenv(t_ms *t)
{
	int	j;

	j = -1;
	while (t->env[++j] != NULL)
		fd_printf(t->output_fd, "%s\n", t->env[j]);
	return (0);
}

int	is_builtins(char *str)
{
	int	is_b;

	is_b = 0;
	if (ft_strncmp("env", str, 4) == 0)
		is_b += 1;
	if (ft_strncmp("clear", str, 6) == 0)
		is_b += 1;
	if (ft_strncmp("pwd", str, 4) == 0)
		is_b += 1;
	if (ft_strncmp("echo", str, 5) == 0)
		is_b += 1;
	if (ft_strncmp("cd", str, 3) == 0)
		is_b += 1;
	if (ft_strncmp("export", str, 7) == 0)
		is_b += 1;
	if (ft_strncmp("unset", str, 6) == 0)
		is_b += 1;
	if (ft_strncmp("exit", str, 6) == 0)
		is_b += 1;
	return (is_b);
}

void	handle_builtins(t_ms *t, int i)
{
	if (ft_strncmp("env", t->cmdl[i][0], 4) == 0)
		t->return_v = printenv(t);
	if (ft_strncmp("clear", t->cmdl[i][0], 5) == 0)
		t->return_v = 0 * printf("\033[2J\033[H");
	if (ft_strncmp("pwd", t->cmdl[i][0], 3) == 0)
		t->return_v = 0 * printf("%s\n", t->pwd);
	if (ft_strncmp("echo", t->cmdl[i][0], 4) == 0)
		t->return_v = ft_echo(t, i);
	if (ft_strncmp("cd", t->cmdl[i][0], 3) == 0)
		t->return_v = ft_cd(t, t->cmdl[i][0]);
	if (ft_strncmp("unset", t->cmdl[i][0], 6) == 0)
		t->return_v = ft_unset(t, i);
	if (ft_strncmp("export", t->cmdl[i][0], 7) == 0)
		t->return_v = ft_export(t, i);
	t->status = (t->return_v << 8);
}
