/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:55:13 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/20 02:35:46 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_remove(t_data *data, t_token *to_remove)
{
	t_token	*tmp;

	if (!data->token || !to_remove)
		return ;
	if (data->token == to_remove)
		ft_token_rmfirst(data, to_remove);
	tmp = data->token;
	while (tmp->next)
	{
		if (tmp->next == to_remove)
		{
			tmp->next = to_remove->next;
			free(to_remove->data);
			free(to_remove);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_token_rmfirst(t_data *data, t_token *to_remove)
{
	t_token	*tmp;

	if (!data->token || !to_remove)
		return ;
	if (data->token == to_remove)
	{
		if (!data->token->next)
		{
			free(data->token->data);
			free(data->token);
			data->token = NULL;
			return ;
		}
		tmp = data->token->next;
		free(data->token->data);
		free(data->token);
		data->token = tmp;
		data->token->prev = NULL;
		return ;
	}
}
