/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:54:21 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/02 16:40:54 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_word_split(t_data *data, t_token *token)
{
	char	**tab;
	size_t	i;
	t_token	*new;

	tab = ft_word_split(token->data);
	if (tab == NULL)
		exit_error(ERROR_MALLOC, NULL, data);
	free(token->data);
	i = 0;
	token->data = tab[i++];
	while (tab[i])
	{
		new = ft_tokennew(tab[i], 0, ft_strlen(tab[i]), WORD);
		if (!new)
			exit_error(ERROR_MALLOC, NULL, data);
		ft_tokenadd_next(token, new);
		i++;
	}
	free(tab);
}

void	word_split(t_data *data)
{
	t_token	*token;
	size_t	i;

	token = data->token;
	while (token)
	{
		i = 0;
		while (token->data[i])
		{
			if (ft_isblank(token->data[i]) == 1)
			{
				do_word_split(data, token);
			}
			i++;
		}
		token = token->next;
	}
}
