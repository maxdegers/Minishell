/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:54:21 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/21 17:23:13 by mbrousse         ###   ########.fr       */
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
		token = new;
		free(tab[i]);
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

int	word_split(t_data *data, int s_quote, int d_quote)
{
	t_token	*token;
	size_t	i;

	token = data->token;
	while (token)
	{
		i = 0;
		while (token->data && token->data[i])
		{
			if (token->data[i] == S_QUOTE)
				s_quote *= -1;
			if (token->data[i] == D_QUOTE)
				d_quote *= -1;
			if (ft_isblank(token->data[i]) == 1
				&& (s_quote != 1 && d_quote != 1))
			{
				if (token->type > 1 && token->type < 5)
					return (ft_put_error(1, EM_ANB), 1);
				do_word_split(data, token);
				break ;
			}
			i++;
		}
		token = token->next;
	}
	return (0);
}
