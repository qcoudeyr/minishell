/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/24 08:08:29 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void printenv(char **envp)
{
	int j;

	j = -1;
	while (envp[++j] != NULL)
		printf("%s\n", envp[j]);
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

		t->cmd[i] = readline("$ "COLOR_RED"minishell"RESET"~: ");

		if (t->cmd[i] == NULL)
			break;
		if (t->cmd[i][0] != '\0')
			add_history(t->cmd[i]);
		if (ft_strncmp("env", t->cmd[i], 4) == 0)
			printenv(t->env);
		if (ft_strncmp("clear", t->cmd[i], 5) == 0)
			printf("\033[2J\033[H");
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

	parsing(t);
	start_minishell(t);

	ft_free(t);
	printf("\033[2J\033[H");
	return (0);
}
