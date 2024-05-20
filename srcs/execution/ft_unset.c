/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 10:05:08 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/20 17:48:59 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_remove_env(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			break ;
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	if (prev == NULL)
		(*env) = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

int	ft_unset(t_block *block, t_data *data)
{
	int	i;

	i = 1;
	while (block->args[i])
	{
		ft_remove_env(&data->env, block->args[i]);
		i++;
	}
	return (0);
}
