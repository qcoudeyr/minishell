/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/23 08:40:58 by  qcoudeyr        ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char *cmd;
	(void)argv;
	(void)envp;

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
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
