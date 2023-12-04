/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:42:16 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 10:50:20 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell"

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
	int	index;

	index = 0;
	t->input_fd = STDIN_FILENO;
	t->output_fd = STDOUT_FILENO;
	while (t->cmdlist[index] != NULL)
	{
		if (is_special(t->cmdlist[index][0]) == 1 ||( t->cmdlist[index +1] != NULL && is_special(t->cmdlist[index + 1][0]) == 1))
		{
			/* Handle here = and, or, pipe*/
			if (is_and(t->cmdlist[index][0]) == 1)
				index++;
			else if(is_or(t->cmdlist[index][0]) == 1)
			{
				/*
				if t->returnsignal < 1; index++; else break ou index += 2;
				 */
				index++;
			}
			else if (is_special(t->cmdlist[index + 1][0]) == 1 && is_and(t->cmdlist[index +1][0]) == 0)
			{
				if (pipe(t->pipefd) == -1)
					perror("pipe");
				else
					t->output_fd = t->pipefd[1];
			}
			else if (is_special(t->cmdlist[index][0]) == 1 && is_and(t->cmdlist[index +1][0]) == 0)
			{
				t->input_fd = t->pipefd[0];
 				if (t->cmdlist[index + 2] != NULL && ft_strnstr(t->cmdlist[index + 2][0], "|", 2) != 0)
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
				index++;
			}
		}
		handle_redirect(t, index);
		if (is_builtins(t->cmdlist[index][0]) > 0)
		{
			handle_builtins(t, index);
		}
		else
		{
			t->pid = fork();
			if (t->pid == -1)
				ft_perror(t, "fork");
			else if (t->pid == 0)
				ft_execve(t, index);
			else
				wait4(t->pid, &t->status, 0, t->rusage);
		}
		index++;
	}
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
