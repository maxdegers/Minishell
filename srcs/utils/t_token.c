/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:41:02 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 14:33:22 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	lt_size(t_token *token)
{
	size_t	i;

	i = 0;
	while (token)
	{
		token = token->next;
		i++;
	}
	return (i);
}

size_t	lt_size_type(t_token *token, t_type type)
{
	size_t	i;

	i = 0;
	while (token)
	{
		if (token->type == type)
			i++;
		token = token->next;
	}
	return (i);
}

t_token	*lt_new(char *value, t_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
		return (free(new), NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

void	lt_addback(t_token **token, t_token *new)
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
}

void	lt_clear(t_token **token)
{
	t_token	*tmp;

	if (!token || !*token)
		return ;
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->value);
		free(*token);
		*token = tmp;
	}
}
