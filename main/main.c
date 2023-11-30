/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/30 11:49:23 by  qcoudeyr        ###   ########.fr       */
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

int	print_header(void)
{
	int		fd;
	char	*str;

	fd = open("./main/header", O_RDONLY);
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
int	start_minishell(t_ms *t)
{
	int	i;
	char *rl_str;
	void *temp;

	i = 0;
	if (print_header( ) == -1)
		return (-1);

	rl_initialize();
	using_history();
	t->cmd = malloc(sizeof(char**));
	t->cmdlist = NULL;
	t->cmd[0] = ft_calloc(2, sizeof(char *));
	rl_str = ft_strjoin("$ "CL_RED"minishell"RESET"~ [", t->pwd);
	temp = (void *) rl_str;
	rl_str = ft_strjoin(rl_str, "] : ");
	free(temp);
	while (ft_strncmp("exit", t->cmd[i], 4) != 0)
	{
		free(t->cmd[i]);
		if (t->cmdlist != NULL)
			ft_freecmdlist(t);
		t->cmdlist = ft_calloc(2, sizeof(char **));
		signal(SIGINT, getsignal);
		t->cmd[i] = readline(rl_str);
		if (t->cmd[i] == NULL)
			break;
		if (t->cmd[i][0] != '\0')
		{
			rl_redisplay();
			add_history(t->cmd[i]);
		}
		if (*t->cmd[i] != 0 && cmdformat(t) != -1)
			exec_cmd(t);
	}
	free(rl_str);
	return (0);
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

void	ft_freecmdlist(t_ms *t)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (t->cmdlist != NULL)
	{
		while (t->cmdlist != NULL && t->cmdlist[i] != NULL)
		{
			while (t->cmdlist[i][j] != NULL)
				free(t->cmdlist[i][j++]);
			free(t->cmdlist[i]);
			t->cmdlist[i] = NULL;
			i++;
		}
		free(t->cmdlist);
	}
	t->cmdlist = NULL;
}

void	ft_free(t_ms *t)
{
	int	i;

	i = 0;
	if (t->cmd != NULL)
	{
		if ((t->cmd[i]) != NULL)
		{
			free(t->cmd[i]);
			i++;
		}
		free(t->cmd);
	}
	i = 0;
	while (t->path[i] != NULL)
		free(t->path[i++]);
	free(t->path);
	free(t->home);
	free(t->pwd);
	if (t->fpath != NULL)
		free(t->fpath);
	free(t);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	*t;
	(void)argv;

	t = malloc(sizeof(t_ms));
	t->env = env;
	t->env = env;
	/* printf("\033[2J\033[H"); */

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	env_pars(t);
	start_minishell(t);
	ft_freecmdlist(t);
	ft_free(t);
	/* printf("\033[2J\033[H"); */
	rl_clear_history();
	return (0);
}
