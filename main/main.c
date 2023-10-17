/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:34:00 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/10/17 14:57:36 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *commande;
	(void)argv;
	(void)envp;

	if (argc > 1)
		return (printf("ERROR: usage ./minishell\n"), 1);
	rl_initialize();
	while (commande[0] != '1')
	{
		commande = readline("minishell : ");
	}
	return 0;
}
