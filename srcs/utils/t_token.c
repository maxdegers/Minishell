/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:41:02 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/02 16:39:19 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_new_add(t_data *data, size_t start, size_t end, int type)
{
	t_token	*new;

	new = ft_tokennew(data->line, start, end, type);
	if (!new)
		exit_error(ERROR_MALLOC, EM_MALLOC, data);
	ft_tokenadd_back(&data->token, new);
}

t_token	*ft_tokennew(char *line, size_t start, size_t end, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	// if (start == end)
	// {
	// 	new->data = ;
	// 	new->type = type;
	// 	new->next = NULL;
	// 	new->prev = NULL;
	// 	return (new);
	// }
	new->data = malloc(sizeof(char) * (end - start + 1));
	if (!new->data)
		return (free(new), NULL);
	ft_strlcpy(new->data, line + start, end - start + 1);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_tokenadd_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!(*token))
	{
		(*token) = new;
		return ;
	}
	tmp = (*token);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_tokenadd_next(t_token *token, t_token *new)
{
	t_token	*tmp;

	if (!token || !new)
		return ;
	tmp = token->next;
	token->next = new;
	new->prev = token;
	new->next = tmp;
	if (tmp)
		tmp->prev = new;
}

void	ft_token_clear(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = tmp;
	}
}

void	ft_tokenprint(t_token *token)
{
	while (token)
	{
		ft_printf("data: %s\t\t\t", token->data);
		ft_printf("type: %d\n", token->type);
		token = token->next;
	}
}
