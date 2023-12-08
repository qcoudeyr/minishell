/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 10:51:17 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/08 11:01:02 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	import_env(t_ms *t)
{
	t->fd = open("./utils/.env", O_RDONLY);
	if (t->fd < 0)
	{
		perror("open");
		return ;
	}
	t->env[t->i] = get_next_line(t->fd);
	while (t->env[t->i] != NULL)
	{
		t->env[t->i][ft_strlen(t->env[t->i]) - 1] = 0;
		t->i++;
		t->env[t->i] = get_next_line(t->fd);
	}
	t->return_v = 1;
}

int	ask_for_env(t_ms *t)
{
	char	*buffer;

	write(1, CL_RED"No env detected, do you want to load default linux env ?", \
62);
	write(1, BOLD" y/n-> "RESET, 16);
	buffer = NULL;
	while (1)
	{
		buffer = get_next_line(0);
		if (ft_strnstr("y\n", buffer, 2) != 0)
		{
			import_env(t);
			break ;
		}
		if (ft_strnstr("n\n", buffer, 2) != 0)
		{
			t->return_v = 0;
			break ;
		}
		buffer = pfree(buffer);
	}
	buffer = pfree(buffer);
	return (t->return_v);
}

int	varlen_env(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (*str == 0)
		return (0);
	while (str[i] != 0 && str[i] != '=')
		i++;
	return (i);
}

void	add_var_env(t_ms *t, char *str, int index)
{
	int		i;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	while (t->env[i] != NULL)
	{
		if (ft_strncmp(t->env[i], str, varlen_env(str)) == 0)
			newenv[i] = ft_strdup(str);
		else
			newenv[i] = ft_strdup(t->env[i]);
		i++;
	}
	if (index < 0)
		newenv[i] = ft_strdup(str);
	i = 0;
	while (t->env[i] != NULL)
	{
		t->env[i] = pfree(t->env[i]);
		i++;
	}
	t->env = pfree(t->env);
	t->env = newenv;
}
