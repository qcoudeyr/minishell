/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:42:16 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/09 11:09:28 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(t_ms *t, int i)
{
	dup2(t->input_fd, 0);
	dup2(t->output_fd, 1);
	if (execve(t->cmdl[i][0], t->cmdl[i], t->env) == -1)
	{
		ft_perror(t, "execve");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_ms *t)
{
	t->index = 0;
	t->input_fd = STDIN_FILENO;
	t->output_fd = STDOUT_FILENO;
	while (t->cmdl[t->index] != NULL)
	{
		handle_spec(t);
		handle_redirect(t, t->index);
		if (t->cmdl[t->index] != NULL && is_builtins(t->cmdl[t->index][0]) > 0)
			handle_builtins(t, t->index);
		else if (t->cmdl[t->index] != NULL)
		{
			t->pid = fork();
			if (t->pid == -1)
				ft_perror(t, "fork");
			else if (t->pid == 0)
				ft_execve(t, t->index);
			else
				wait4(t->pid, &t->status, 0, t->rusage);
		}
		t->index++;
		t->return_v = (t->status >> 8);
		env_pars(t);
	}
}

void	handle_spec(t_ms *t)
{
	if (is_special(t->cmdl[t->index][0]) == 1 || (t->cmdl[t->index + 1] \
	!= NULL && is_special(t->cmdl[t->index + 1][0]) == 1))
	{
		if (is_and(t->cmdl[t->index][0]) == 1)
			t->index++;
		else if (is_or(t->cmdl[t->index][0]) == 1)
		{
			if (t->status != 0)
				t->index++;
			else
				t->index += 2;
		}
		else if (is_special(t->cmdl[t->index + 1][0]) == 1 && \
	(is_and(t->cmdl[t->index +1][0]) + is_or(t->cmdl[t->index +1][0])) == 0)
		{
			if (pipe(t->pipefd) == -1)
				perror("pipe");
			else
				t->output_fd = t->pipefd[1];
		}
		else if (is_special(t->cmdl[t->index][0]) == 1 && \
		is_and(t->cmdl[t->index +1][0]) == 0)
			end_pipe(t);
	}
}

void	end_pipe(t_ms *t)
{
	t->input_fd = t->pipefd[0];
	if (t->cmdl[t->index + 2] != NULL && \
	ft_strnstr(t->cmdl[t->index + 2][0], "|", 2) != 0)
	{
		if (pipe(t->pipefd) == -1)
			perror("pipe");
		else
		{
			close(t->output_fd);
			t->output_fd = t->pipefd[1];
		}
	}
	else
	{
		close(t->pipefd[1]);
		t->output_fd = STDOUT_FILENO;
	}
	t->index++;
}

int	handle_redirect(t_ms *t, int index)
{
	int	i;

	i = 0;
	if (check_redirect_error == -1)
		return (-1);
	while (t->cmdl[index] != NULL && t->cmdl[index][i] != NULL)
	{
		if (t->cmdl[index][i][0] == '<')
			input_redirect(t, index, i);
		else if (t->cmdl[index][i][0] == '>')
			output_redirect(t, index, i);
		i++;
	}
	if (t->input_fd == -1 || t->output_fd == -1)
		return (ft_perror(t, "open"));
}

void	check_redirect_error(t_ms *t, int index)
{
	int		i;
	char	*temp;

	i = 0;
	t->temp = NULL;
	temp = NULL;
	while (t->cmdl[index] != NULL && t->cmdl[index][i] != NULL)
	{
		if (t->cmdl[index][i][0] == '<' && t->cmdl[index][i + 1] != NULL)
			t->temp = t->cmdl[index][i + 1];
		else if (ft_strchr(t->cmdl[index][i], '>') != 0 && t->cmdl[index][i + 1] != NULL)
			temp = t->cmdl[index][i + 1];
		if (temp != NULL && t->temp != NULL)
			break;
		i++;
	}
	if (ft_strcmp(temp, t->temp) == 0)
	{
		printf("%s: input file is output file", t->cmdl[index][0]);
		t->status = 512;
		return (2);
	}
	return (0);
}
