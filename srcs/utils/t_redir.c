/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_redir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:17:42 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/17 12:56:46 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*ft_redir_new(char *data, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(data);
	new->type = type;
	new->next = NULL;
	new->fd = -1;
	return (new);
}

void	ft_redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir	*tmp;

	if (!(*redir))
	{
		(*redir) = new;
		return ;
	}
	tmp = (*redir);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_add_redir(t_block *block, t_token *token, t_data *data)
{
	t_redir	*new;

	new = ft_redir_new(token->data, token->type);
	if (!new)
		exit_error(ERROR_MALLOC, NULL, data);
	new->is_in_cote = token->is_in_cote;
	ft_redir_add_back(&block->redir, new);
}

void	ft_redir_free(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}
