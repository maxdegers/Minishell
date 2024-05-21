/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:54:21 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/21 12:26:25 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_word_split(t_data *data, t_token *token)
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

int	word_check(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (ft_islineblank(token->data) == 1)
		{
			if (data->token == token)
				ft_token_rmfirst(data, token);
			else
				ft_token_remove(data, token);
			token = data->token;
		}
		else if (token)
			token = token->next;
	}
	if (data->token == NULL)
		return (1);
	return (0);
}

int	word_split(t_data *data, bool s_quote, bool d_quote)
{
	t_token	*token;
	size_t	i;

	token = data->token;
	while (token)
	{
		i = 0;
		while (token->data[i])
		{
			if (token->data[i] == S_QUOTE && d_quote == false)
				s_quote = !s_quote;
			if (token->data[i] == D_QUOTE && s_quote == false)
				d_quote = !d_quote;
			if (ft_isblank(token->data[i]) == 1
				&& (s_quote == false || d_quote == false))
			{
				if (token->type > 1 && token->type < 5)
					return (ft_put_error(1, EM_ANB), 1);
				do_word_split(data, token);
			}
			i++;
		}
		token = token->next;
	}
	return (0);
}
