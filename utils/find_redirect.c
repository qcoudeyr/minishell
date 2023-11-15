/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:18:44 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/15 21:58:24 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redirect(int *fd, char **cmd)
{
	int i;

	i = 0;
	while ((ft_strncmp(cmd[i], ">", 1) != 0 && ft_strncmp(cmd[i], ">>", 2) != 0 && cmd[i + 1] != NULL))
		i++;
	if (cmd[i] != NULL)
	{
		if(ft_strncmp(cmd[i], ">", 1) == 0)
			*fd = open(cmd[i+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		else
			*fd = open(cmd[i+1], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	}
	else
		*fd = 1;
	return 1;
}