/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultinexe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 09:45:55 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/17 12:59:04 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_env(t_ms *t, char *var, char *tochange)
{
	void	*ptr;

	if (ft_strncmp(var, "PWD=", 5) == 0)
	{
		t->pwd = pfree(t->pwd);
		t->pwd = ft_strdup(tochange);
	}
	ptr = ft_strjoin(var, tochange);
	add_var_export(t, ptr, -1);
	ptr = pfree(ptr);
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
	if (ft_strncmp("pwd", t->cmdl[i][0], 3) == 0)
		t->return_v = ft_pwd(t);
	if (ft_strncmp("echo", t->cmdl[i][0], 4) == 0)
		t->return_v = ft_echo(t, i);
	if (ft_strncmp("cd", t->cmdl[i][0], 3) == 0)
		t->return_v = ft_cd(t, t->cmdl[i]);
	if (ft_strncmp("unset", t->cmdl[i][0], 6) == 0)
		t->return_v = ft_unset(t, i);
	if (ft_strncmp("export", t->cmdl[i][0], 7) == 0)
		t->return_v = ft_export(t, i);
	if (ft_strncmp("exit", t->cmdl[i][0], 5) == 0)
		t->return_v = ft_exit(t);
	t->status = (t->return_v << 8);
}
