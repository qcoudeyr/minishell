/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/23 07:07:16 by  qcoudeyr        ###   ########.fr       */
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
	char *commande;
	(void)argv;
	(void)envp;

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	rl_initialize();
	while (ft_strncmp("exit", commande, 5) != 0)
	{
		commande = readline("minishell : ");
		if (ft_strncmp("env", commande, 4) == 0)
			printenv(envp);
	}
	return 0;
}
