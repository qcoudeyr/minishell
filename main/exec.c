/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:42:16 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 12:54:00 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(t_ms *t, int i)
{
	dup2(t->input_fd, 0);
	dup2(t->output_fd, 1);
	if (execve(t->cmdlist[i][0], t->cmdlist[i], t->env) == -1)
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
	while (t->cmdlist[t->index] != NULL)
	{
		handle_spec(t);
		handle_redirect(t, t->index);
		if (is_builtins(t->cmdlist[t->index][0]) > 0)
		{
			handle_builtins(t, t->index);
		}
		else
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
	}
}

void	handle_spec(t_ms *t)
{
	if (is_special(t->cmdlist[t->index][0]) == 1 || (t->cmdlist[t->index + 1] \
	!= NULL && is_special(t->cmdlist[t->index + 1][0]) == 1))
	{
		if (is_and(t->cmdlist[t->index][0]) == 1)
			t->index++;
		else if (is_or(t->cmdlist[t->index][0]) == 1)
		{
//			if t->returnsignal < 1; t->index++; else break ou t->index += 2;
			t->index++;
		}
		else if (is_special(t->cmdlist[t->index + 1][0]) == 1 && \
		is_and(t->cmdlist[t->index +1][0]) == 0)
		{
			if (pipe(t->pipefd) == -1)
				perror("pipe");
			else
				t->output_fd = t->pipefd[1];
		}
		else if (is_special(t->cmdlist[t->index][0]) == 1 && \
		is_and(t->cmdlist[t->index +1][0]) == 0)
			end_pipe(t);
	}
}

void	end_pipe(t_ms *t)
{
	t->input_fd = t->pipefd[0];
	if (t->cmdlist[t->index + 2] != NULL && \
	ft_strnstr(t->cmdlist[t->index + 2][0], "|", 2) != 0)
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

void	handle_redirect(t_ms *t, int index)
{
	int	i;

	i = 0;
	while (t->cmdlist[index][i] != NULL)
	{
		if (t->cmdlist[index][i][0] == '<')
			input_redirect(t, index, i);
		else if (t->cmdlist[index][i][0] == '>')
			output_redirect(t, index, i);
		i++;
	}
	if (t->input_fd == -1 || t->output_fd == -1)
		ft_perror(t, "open");
}
