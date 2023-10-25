/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:10:26 by qcoudeyr          #+#    #+#             */
/*   Updated: 2023/10/24 14:12:47 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *str, const char *tosearch, size_t len)
{
	int		n;
	char	*ptr;
	size_t	i;

	if (!tosearch || *tosearch == 0)
		return ((char *)str);
	i = 0;
	while (str != NULL && i < len && str[i])
	{
		n = 0;
		ptr = (char *)&str[i];
		while (str[i + n] == tosearch[n] && i + n < len)
		{
			if (tosearch[n +1] == 0)
				return (ptr);
			n++;
		}
		i++;
	}
	return (NULL);
}
