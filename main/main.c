/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/23 09:13:52 by  qcoudeyr        ###   ########.fr       */
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

int	print_header(char **envp)
{
	int		fd;
	char	*str;
	char	*args[2];

	args[0] = "clear";
	args[1] = NULL;
	execve("/usr/bin/clear", args, envp);
	
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

int	main(int argc, char **argv, char **envp)
{
	char *cmd;
	(void)argv;
	(void)envp;

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	if (print_header(envp) == -1)
		return (-1);
	rl_initialize();
	cmd = malloc(sizeof(char*));
	while (ft_strncmp("exit", cmd, 4) != 0)
	{
		free(cmd);
		cmd = readline("$ "COLOR_RED"minishell"RESET"~: ");
		if (ft_strncmp("env", cmd, 4) == 0)
			printenv(envp);
	}
	free(cmd);
	return 0;
}
