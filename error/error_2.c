/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:52:11 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/07 08:35:58 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(t_ms *t, char *s)
{
	if (s != NULL)
		perror(s);
	write(t->output_fd, "2", 2);
	exit(EXIT_FAILURE);
}
