/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/30 17:04:18 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setenv(t_data *data, char *var, char *val)
{
	t_env	*tmp;

	tmp = ft_envfind(data->env, var);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(val);
	}
	else
		ft_envadd_back(&data->env, ft_envnew(ft_strdup(var), ft_strdup(val)));
}

t_env	*ft_put_env(t_env *env)
{
	size_t	i;
	size_t	j;
}

void	ft_put_env_exp(t_data *data)
{
	t_env	*env_alph;
	t_env	*tmp;
	char	alph;

	tmp = data->env;
	alph = tmp->name[0];
	while (tmp)
	{
		if ()
		tmp = tmp->next;
	}
}

int	ft_export(t_data *data, t_block *block)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*val;

	i = -1;
	if (!block->args[1])
		ft_put_env_exp(data);
	while (block->args[++i])
	{
		j = 0;
		while (block->args[i][j] && block->args[i][j] != '=')
			j++;
		if (block->args[i][j] == '=')
		{
			var = ft_substr(block->args[i], 0, j);
			val = ft_substr(block->args[i], j + 1, ft_strlen(block->args[i]) - j - 1);
			ft_setenv(data, var, val);
			free(var);
			free(val);
		}
	}
	return (0);
}
