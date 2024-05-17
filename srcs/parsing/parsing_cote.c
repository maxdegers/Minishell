/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:00:31 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/17 12:53:08 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cote_remove(t_token *token, char quote, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == S_QUOTE || token->data[i] == D_QUOTE)
		{
			token->is_in_cote = 1;
			quote = token->data[i];
			i += 1;
			while (token->data[i] && token->data[i] != quote)
			{
				if (token->data[i++] == quote)
					break ;
				new[j++] = token->data[i - 1];
			}
			i += 1;
		}
		else
			new[j++] = token->data[i++];
	}
	free(token->data);
	token->data = new;
}

size_t	calc_cote(t_token *token, char quote, size_t size)
{
	size_t	i;

	i = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == S_QUOTE || token->data[i] == D_QUOTE)
		{
			quote = token->data[i];
			i += 1;
			while (token->data[i] && token->data[i] != quote)
			{
				if (token->data[i++] == quote)
					break ;
				size += 1;
			}
			i += 1;
		}
		else
		{
			size += 1;
			i += 1;
		}
	}
	return (size);
}

void	ft_parsing_quote(t_data *data)
{
	t_token	*token;
	size_t	size;
	char	*new;

	token = data->token;
	while (token)
	{
		size = calc_cote(token, 0, 0);
		new = ft_calloc(sizeof(char), size + 1);
		if (!new)
			exit_error(ERROR_MALLOC, NULL, data);
		do_cote_remove(token, 0, new);
		token = token->next;
	}
}
