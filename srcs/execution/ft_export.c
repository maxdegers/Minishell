/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:39:52 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/26 16:26:48 by mpitot           ###   ########.fr       */
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

void	ft_export(t_data *data, t_block *block)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*val;

	i = -1;
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
}
