/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Splitlikeshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheinric <lheinric@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:20:59 by lheinric          #+#    #+#             */
/*   Updated: 2023/11/18 20:13:29 by lheinric         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	sp_wordcnt(char *str, char c)
{
	int i;
	int j;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		j = 0;
		if(str[i] == '"')
		{
			while(str[i+(++j)])
			{
				if (str[i+j] == '"')
				{
					count++;
					i += j;
					break;
				}
			}
		}
		if (str[i] == c)
			count++;
	}
	return (count);
}

static size_t	sp_widgetlen(const char *s, char chr)
{
	int	c;

	c = 0;
	while (*s != '"' && *s != 0)
	{
		c++;
		s++;
	}
	return (c);
}

static size_t	sp_wordlen(const char *s, char chr)
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

static char	**sp_empty_tab(void)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *));
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	return (tab);
}

char	**splititlikeshell(char const *str, char c)
{
	int		i;
	int		j;
	int		index;
	char	**tab;
	char	*s;

	s = ft_strdup(str);
	if (!str || *s == '\0')
		return (sp_empty_tab());
	i = 0;
	j = 0;
	index = 0;
	tab = (char **)malloc(sizeof(char *) * (sp_wordcnt(s, c) + 1));
	
	tab[index] = NULL;
	free (s);
	return (tab);
}

while (s[i] != 0 || (s[i] == c && s[i + 1] == 0))
	{
		while (s[i] == c && s[i] != 0)
			i++;
		tab[index] = malloc(sizeof(char) * ft_wordlen(&s[i], c) + 1);
		ft_strlcpy(tab[index++], &s[i], ft_wordlen(&s[i], c) + 1);
		i += ft_wordlen(&s[i], c);
	}
