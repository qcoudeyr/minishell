/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:38:45 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/04 11:25:07 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fd_printf.h"

static int	print_nbrbase(int len, char *dts, unsigned long n, int b_l)
{
	char	*buffer;
	int		i;

	buffer = malloc (sizeof(char) * len +1);
	buffer[len] = 0;
	i = len - 1;
	while (i >= 0)
	{
		buffer[i] = dts[(n % b_l)];
		n /= b_l;
		i--;
	}
	write(fd, buffer, len);
	free (buffer);
	return (len);
}

int	fd_putnbr_base(int fd, unsigned long long n, char *base)
{
	int						len ;
	unsigned long long		temp;
	int						base_len;

	base_len = ft_strlen(base);
	len = 0;
	temp = n;
	if (n == 0)
		return (write(fd, "0", 1));
	while (n > 0)
	{
		len++;
		n /= base_len;
	}
	return (print_nbrbase(fd, len, base, temp, base_len));
}
