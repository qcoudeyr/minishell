/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  qcoudeyr <@student.42perpignan.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:28:07 by  qcoudeyr         #+#    #+#             */
/*   Updated: 2023/12/05 16:29:22 by  qcoudeyr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	varlen_env(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == 0)
		return (0);
	while (str[i] != 0 && str[i] != '=')
		i++;
	return (i);
}

void	add_var_env(t_ms *t, int index)
{
	int		i;
	int		j;
	char	**newenv;

	newenv = ft_calloc(1000, sizeof(char *));
	i = 0;
	j = 0;
	while (t->env[i] != NULL)
	{
		if (i == index)
			i++;
		if (t->env[i] != NULL)
			newenv[j++] = ft_strdup(t->env[i++]);
	}
	j = 0;
	while (t->env[j] != NULL)
		pfree(t->env[j++]);
	pfree(t->env);
	t->env = newenv;
}

void	ft_export(t_ms *t, int i)
{
	int		j;
	int		index;

	j = 1;
	index = 0;
	while (t->cmdlist[i][j] != NULL)
	{

		while (t->env[index] != NULL)
		{
			if (ft_strncmp(t->env[index], t->cmdlist[i][j], ft_strlen(t->cmdlist[i][j])) == 0)
			{
				remove_var_env(t, index);
				break ;
			}
			index++;
		}
		j++;
	}

}

char	*set_env_var(char *cmd)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!cmd || !cmd)
		return (cmd);
	if (is_set_env_var(cmd) == 0)
		return (cmd);
	temp = ft_calloc(ft_strlen(cmd), sizeof(char));
	while (cmd[i] != 0)
	{
		while (cmd[i] != 0 && cmd[i] != '=')
			i++;
		if (cmd[i] == '=')
		{
			j = (i++ - 1);
			while (j != 0 && ft_isalpha(cmd[j]) == 1)
				j--;
			while (cmd[i] != 0 && (\
ft_isalpha(cmd[i]) == 1 || ft_isalnum(cmd[i]) == 1))
				i++;
			ft_strlcpy(temp, (cmd + j), (i - j) + 1);
			printf("%s \n", temp);
		}
	}
	free(temp);
	return (cmd);
}
