/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:05:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 15:03:39 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_env(t_env *env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->name);
			free(tmp->value);
			if (prev)
				prev->next = tmp->next;
			else
				env = tmp->next;
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_block *block, t_data *data)
{
	int	i;

	i = 1;
	while (block->args[i])
	{
		ft_remove_env(data->env, block->args[i]);
		i++;
	}
	return (0);
}