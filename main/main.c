/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/23 10:40:10 by  qcoudeyr        ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char *cmd;
	(void)argv;
	(void)envp;

	printf("\033[2J\033[H");
	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	if (print_header( ) == -1)
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
