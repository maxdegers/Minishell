/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:03:37 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/08 12:14:28 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	clac_size_block(t_token *token)
{
	size_t	size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp && ft_strcmp(tmp->data, "|") != 0)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

void	ft_set_redir(t_token *tmp, t_block *block, t_data *data)
{
	int		i;
	t_token	*tmp2;

	i = 0;
	while (tmp && ft_strcmp(tmp->data, "|") != 0)
	{
		if (tmp->type == REDIR_HEREDOC)
			i++;
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_HEREDOC)
		{
			ft_add_redir(block, tmp->data, tmp->type, data);
			tmp2 = tmp->next;
			ft_token_remouve(data, tmp);
			i++;
			tmp = tmp2;
		}
		else if (tmp)
			tmp = tmp->next;
	}
	block->heredoc_exp = i;
	ft_printf("ft_set_redir\n");
	ft_tokenprint(data->token);
}

void	ft_set_block(t_data *data)
{
	t_block	*block;
	char	**args;
	size_t	i;

	while (data->token)
	{
		block = ft_block_new(data);
		i = 0;
		ft_set_redir(data->token, block, data);
		block->cmd = ft_strdup(data->token->data);
		args = ft_calloc(sizeof(char *), (clac_size_block(data->token) + 1));
		while (data->token && ft_strcmp(data->token->data, "|") != 0)
		{
			args[i++] = ft_strdup(data->token->data);
			data->token = data->token->next;
		}
		block->args = args;
		if (data->token)
			data->token = data->token->next;
	}
}
