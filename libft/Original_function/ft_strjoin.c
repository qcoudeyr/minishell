/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:51:56 by qcoudeyr          #+#    #+#             */
/*   Updated: 2023/12/06 12:04:22 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc((len + 2), sizeof(char));
	if (!str)
		return (NULL);
	while (s1 != NULL && *s1)
		*str++ = *(char *)s1++;
	while (s2 != NULL && *s2)
		*str++ = *(char *)s2++;
	*str = 0;
	return (str - len);
}
