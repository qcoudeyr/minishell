/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:53:15 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/11/21 10:03:15 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char **test;

	test = ft_splitq("echo \"ceci est un test\"");
	for (int i = 0; test[i] != 0; i++)
		printf("%s\n",test[i]);
	return 0;
}

