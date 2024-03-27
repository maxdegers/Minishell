/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:55:41 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 17:57:09 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd_type(t_data data)
{
	t_token	*tmp;

	tmp = data.token;
	while (tmp)
	{
//		if (tmp->type == WORD &&)
		tmp = tmp->next;
	}
	return (0);
}
