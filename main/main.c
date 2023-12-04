/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 10:46:28 by  qcoudeyr        ###   ########.fr       */
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
	while(str != NULL)
	{
		printf("%s",str);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (0);
}

void	init_cmdlist(t_ms *t)
{
	if (t->cmdlist != NULL)
		ft_freecmdlist(t);
	t->cmdlist = ft_calloc(2, sizeof(char **));
}

char	*rl_string(t_ms *t, char *rl_str)
{
	void *temp;

	if (rl_str != NULL)
		pfree(rl_str);
	rl_str = ft_strjoin("$ "CL_RED"minishell"RESET"~ [", t->pwd);
	temp = (void *) rl_str;
	rl_str = ft_strjoin(rl_str, "] : ");
	pfree(temp);
	return (rl_str);
}
int	start_minishell(t_ms *t)
{
	int		i;
	char	*rl_str;

	i = 0;
	rl_str = NULL;
	if (print_header == -1)
		return (-1);
	rl_initialize();
	using_history();
	t->cmd = malloc(sizeof(char **));
	t->cmd[0] = ft_calloc(2, sizeof(char *));
	while (ft_strncmp("exit", t->cmd[i], 4) != 0)
	{
		pfree(t->cmd[i]);
		init_cmdlist(t);
		signal(SIGINT, getsignal);
		rl_str = rl_string(t, rl_str);
		t->cmd[i] = readline(rl_str);
		if (t->cmd[i] == NULL)
			break ;
		if (t->cmd[i][0] != '\0')
		{
			rl_redisplay();
			add_history(t->cmd[i]);
		}
		if (*t->cmd[i] != 0 && cmdformat(t) != -1)
			exec_cmd(t);
	}
	pfree(rl_str);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	*t;

	(void)argv;
	t = malloc(sizeof(t_ms));
	t->rusage = ft_calloc(1, sizeof(struct rusage));
	t->env = env;
	t->env = env;
	t->cmdlist = NULL;
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
