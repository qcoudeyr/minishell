/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:54:47 by lheinric          #+#    #+#             */
/*   Updated: 2023/10/24 12:50:34 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_pwd(t_ms *t)
{
	if (t->pwd != NULL)
	{
		printf("%s\n", t->pwd);
		return (1);
	}
	else
		return (0);
}