/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:49:49 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/30 12:58:43 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_expansion(t_data *data)
{
	t_token	*tmp;
	int		i;

	tmp = data->token;
	while (tmp)
	{
		i = 0;
		while (tmp->data[i])
		{
			
		}
		tmp = tmp->next;
	}
}