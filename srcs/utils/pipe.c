/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:55:48 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/18 21:05:32 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_token(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (data->token->type == PIPE)
		{
			ft_put_error(1, "syntax error near unexpected token `|'\n");
			return (1);
		}
		if (!token->next && token->type == PIPE)
		{
			ft_put_error(1, "syntax error near unexpected token `|'\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
