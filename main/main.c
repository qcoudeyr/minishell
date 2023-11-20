/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/20 12:20:55 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execve(t_ms *t, int i)
{
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

	i = 0;
	if (print_header( ) == -1)
		return (-1);

	rl_initialize();
	using_history();
	t->cmd = malloc(sizeof(char**));
	t->cmd[0] = malloc(sizeof(char *));
	t->cmd[0][0] = '\0';
	while (ft_strncmp("exit", t->cmd[i], 4) != 0)
	{
		free(t->cmd[i]);
		signal(SIGINT, getsignal);
		rl_str = ft_strjoin("$ "CL_RED"minishell"RESET"~", t->pwd);
		t->cmd[i] = readline(ft_strjoin(rl_str, " : "));

		if (t->cmd[i] == NULL)
			break;
		if (t->cmd[i][0] != '\0')
		{
			rl_redisplay();
			add_history(t->cmd[i]);
		}
		if (*t->cmd[i] != 0 && cmdformat(t) != -1 && is_builtins(t,i) == 0 )
		{
			for(int x = 0; t->cmdlist[i][x] != NULL; x++)
				printf("%i = %s\n",x, t->cmdlist[i][x]);

			t->pid = fork();
			if (t->pid == -1)
				ft_perror(t, "fork");
			else if (t->pid == 0)
				ft_execve(t, i);
			else
			{
				waitpid(t->pid, &t->status, 0);
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
		while (t->cmdlist != NULL && t->cmdlist[i] != NULL)
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
	free(t->pwd);
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
	t->infile = malloc(sizeof(char *));
	t->outfile = malloc(sizeof(char *));
	t->infile = 0;
	t->outfile = 0;
	t->env = env;
	t->env = env;
	printf("\033[2J\033[H");

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	env_pars(t);
	start_minishell(t);

	ft_free(t);
	printf("\033[2J\033[H");
	rl_clear_history();
	return (0);
}
