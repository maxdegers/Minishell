/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:49:49 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/30 22:29:21 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type(t_token *token)
{
	if (ft_strcmp(token->data, ">") == 0)
		token->type = REDIR_OUT;
	else if (ft_strcmp(token->data, ">>") == 0)
		token->type = REDIR_APPEND;
	else if (ft_strcmp(token->data, "<") == 0)
		token->type = REDIR_IN;
	else if (ft_strcmp(token->data, "<<") == 0)
		token->type = REDIR_HEREDOC;
	else if (ft_strcmp(token->data, "|") == 0)
		token->type = PIPE;
}

void	ft_redir_expansion(t_data *data)
{
	t_token	*tmp;
//	int		i;

	tmp = data->token;
	while (tmp)
	{
//		i = 0;
		set_type(tmp);
		tmp = tmp->next;
	}
}
