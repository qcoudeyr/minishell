/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/24 10:02:56 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(t_ms *t, int i)
{
	dup2(t->file_fd[0], 0);
	dup2(t->pipefd[1], 1);
	if (t->cmdlist[i +1] == NULL)
		dup2(t->file_fd[1], 1);
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

	i = 0;
	if (print_header( ) == -1)
		return (-1);

	rl_initialize();
	using_history();

	t->cmd = malloc(sizeof(char**));
	t->cmd[0] = malloc(sizeof(char *));

	while (ft_strncmp("exit", t->cmd[i], 4) != 0)
	{
		free(t->cmd[i]);
		signal(SIGINT, getsignal);
		t->cmd[i] = readline("$ "COLOR_RED"minishell"RESET"~: ");

		if (t->cmd[i] == NULL)
			break;
		if (t->cmd[i][0] != '\0')
			add_history(t->cmd[i]);
		if (is_builtins(t,i) == 0 && cmdformat(t) != -1)
		{
			pipe(t->pipefd);
			t->pid = fork();
			if (t->pid == -1)
				ft_perror(t, "fork");
			else if (t->pid == 0)
				ft_execve(t, i);
			else
			{
				waitpid(t->pid, &t->status, WNOHANG);
				t->file_fd[0] = t->pipefd[0];
				close(t->pipefd[1]);
			}
		}
	}
	return (0);
}

void	ft_freecmdlist(t_ms *t)
{
	int	i;
	int	y;

	i = 0;
	if (t->cmdlist != NULL)
	{
		while (i < (t->narg + 1))
		{
			if (t->cmdlist[i] != NULL)
			{
				y = 0;
				while (t->cmdlist[i][y] != NULL)
					free(t->cmdlist[i][y++]);
			}
			free(t->cmdlist[i]);
			i++;
		}
		free(t->cmdlist);
	}
}

void	ft_free(t_ms *t)
{
	int	i;

	i = 0;
	if (t->cmd != NULL)
	{
		while (i <= t->narg + 1)
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
	ft_freecmdlist(t);
	free(t->infile);
	free(t->outfile);
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

	printf("\033[2J\033[H");

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	env_pars(t);
	start_minishell(t);

	ft_free(t);
	printf("\033[2J\033[H");
	return (0);
}
