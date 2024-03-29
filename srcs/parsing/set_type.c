/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:55:41 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 10:31:36 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->pos == 0 && tmp->type == WORD)
			tmp->cmd_t = CMD;
		else if (tmp->type == WORD)
			tmp->cmd_t = ARGS;
		else if (tmp->type == SIMPLE_COTE || tmp->type == DOUBLE_COTE)
		{
			if (tmp->next && tmp->next->type == STRING)
			{
				tmp->next->cmd_t = ARGS;
				tmp->next->type = tmp->type;
				tmp->type = RM;
				tmp = tmp->next;
			}
			else
				tmp->type = RM;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	rm_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == RM)
		{
			lt_remove(data, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
