/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:24:27 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/09 23:54:46 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *input)
{
	int		length;
	char	*result;
	int		j;
	int		i;

	if (!input)
		return (NULL);
	length = (int)ft_strlen(input);
	result = ft_calloc(length + 2, sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (i < length)
	{
		if (input[i] == '"' && input[length - (i + 1)] == '"')
			i++;
		else
			result[j++] = input[i++];
	}
	result[j] = '\0';
	free(input);
	return (result);
}
