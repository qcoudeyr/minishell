/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 22:36:22 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_header(void)
{
	int		fd;
	char	*str;

	fd = open("./main/header", O_RDONLY);
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

char	*rl_string(t_ms *t, char *rl_str)
{
	void	*temp;

	if (rl_str != NULL)
		rl_str = pfree(rl_str);
	rl_str = ft_strjoin("$ "CL_RED"minishell"RESET"~ [", t->pwd);
	temp = (void *) rl_str;
	rl_str = ft_strjoin(rl_str, "] : ");
	temp = pfree(temp);
	return (rl_str);
}

int	start_minishell(t_ms *t)
{
	char	*rl_str;

	rl_str = NULL;
	while (t->exit == 0)
	{
		init_cmdl(t);
		rl_str = rl_string(t, rl_str);
		t->cmd[t->nc] = readline(rl_str);
		if (t->cmd[t->nc] == NULL || ft_strncmp(t->cmd[t->nc], "exit", 5) == 0)
			break ;
		if (t->cmd[t->nc][0] != '\0')
		{
			rl_redisplay();
			add_history(t->cmd[t->nc]);
		}
		if (*t->cmd[t->nc] != 0 && cmdformat(t) != -1)
			exec_cmd(t);
		env_pars(t);
		if (access("./utils/temp", F_OK) != -1)
			unlink("./utils/temp");
		t->nc++;
	}
	rl_str = pfree(rl_str);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	*t;

	(void)argv;
	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	t = malloc(sizeof(t_ms));
	t_init(t);
	rl_initialize();
	using_history();
	get_env(t, env);
	handle_signal(t);
/* 	printf("\033[2J\033[H"); */
	if (print_header() == -1)
		return (-1);
	start_minishell(t);
/* 	printf("\033[2J\033[H"); */
	rl_clear_history();
	ft_freecmdl(t);
	ft_free(t);
	return (0);
}
