/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:41:02 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 16:42:38 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_tokennew(char *line, int start, int end, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
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
		printf("data: %s\t\t\t", token->data);
		printf("type: %d\n", token->type);
		token = token->next;
	}
}
