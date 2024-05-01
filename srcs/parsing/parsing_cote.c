/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:31 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/01 17:06:00 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parsing_cote(t_data *data)
{
	t_token	*token;
	size_t	i;
	char	quote;

	i = 0;
	token = data->token;
	quote = 0;
	while (token)
	{
		while (token->data[i])
		{
			if (token->data[i] == '\'' || token->data[i] == '\"')
			{
				quote = token->data[i];
				i += 1;
				while (token->data[i] && token->data[i] != quote)
					i += 1;
			}
			i += 1;
		}
		token = token->next;
	}
}