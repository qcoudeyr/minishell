/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:52:02 by qcoudeyr          #+#    #+#             */
/*   Updated: 2023/12/05 16:50:56 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*src;

	if (!s)
		return (0);
	src = (char *) s;
	while (*src)
	{
		if (*src == (char)c)
			return (src);
		src++;
	}
	if (*src == 0 && (char)c == 0)
		return ((char *)src);
	return (0);
}
