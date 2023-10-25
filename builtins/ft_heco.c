/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heco.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:56:50 by lheinric          #+#    #+#             */
/*   Updated: 2023/10/25 11:33:43 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

echo_redirect

int	ft_heco(t_ms *t, char **ordre)
{
	int i;
	int j;

	t_heco heco;

	i = -1
	while(ordre[++i] != NULL)
	{
		j = -1
		while (ordre[i][++j])
		{
			if (ordre[i][0] == '-' && ordre[i][1] == 'n')
				heco.nobackslash = 1;
		}
	}
}
