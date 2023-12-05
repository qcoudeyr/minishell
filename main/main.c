/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 18:46:44 by  qcoudeyr        ###   ########.fr       */
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

void	init_cmdlist(t_ms *t)
{
	if (t->cmdlist != NULL)
		ft_freecmdlist(t);
	t->cmdlist = ft_calloc(2, sizeof(char **));
}

char	*rl_string(t_ms *t, char *rl_str)
{
	void	*temp;

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
		env_pars(t);
	}
	pfree(rl_str);
	return (0);
}
void	get_env(t_ms *t, char **env)
{
	t->env = ft_calloc(1000, sizeof(char *));
	t->i = 0;
	while (env[t->i] != NULL)
	{
		t->env[t->i] = ft_strdup(env[t->i]);
		t->i++;
	}
	t->env[t->i] = NULL;
	env_pars(t);
}

int	main(int argc, char **argv, char **env)
{
	t_ms	*t;

	(void)argv;
	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	t = malloc(sizeof(t_ms));
	t->rusage = ft_calloc(1, sizeof(struct rusage));
	t->cmdlist = NULL;
	t->cmd = malloc(sizeof(char **));
	t->cmd[0] = ft_calloc(2, sizeof(char *));
	t->path = ft_calloc(1, sizeof(char **));
	t->home = ft_calloc(1, sizeof(char *));
	t->pwd = ft_calloc(1, sizeof(char *));
	t->env = ft_calloc(1, sizeof(char **));
	rl_initialize();
	using_history();
	get_env(t, env);
	/* printf("\033[2J\033[H"); */
	if (print_header() == -1)
		return (-1);
	start_minishell(t);
	ft_freecmdlist(t);
	ft_free(t);
	/* printf("\033[2J\033[H"); */
	rl_clear_history();
	return (0);
}
