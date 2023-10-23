/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:59:47 by qcoudeyr          #+#    #+#             */
/*   Updated: 2023/09/28 09:42:18 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_wordlen(const char *s, char chr)
{
	int	c;

	c = 0;
	while (*s != 0 && *s != chr)
	{
		c++;
		s++;
	}
	return (c);
}

static char	**ft_empty_tab(void)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		index;
	char	**tab;
	char	*s;

	s = ft_strdup(str);
	if (!str || *s == '\0')
		return (ft_empty_tab());
	i = 0;
	index = 0;
	tab = (char **)malloc(sizeof(char *) * (ft_wordct(s, c) + 1));
	while (s[i] != 0 || (s[i] == c && s[i + 1] == 0))
	{
		while (s[i] == c && s[i] != 0)
			i++;
		tab[index] = malloc(sizeof(char) * ft_wordlen(&s[i], c) + 1);
		ft_strlcpy(tab[index++], &s[i], ft_wordlen(&s[i], c) + 1);
		i += ft_wordlen(&s[i], c);
	}
	tab[index] = NULL;
	free (s);
	return (tab);
}
