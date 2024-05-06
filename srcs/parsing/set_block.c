/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:03:37 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/06 15:15:24 by mbrousse         ###   ########.fr       */
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
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_HEREDOC)
		{
			ft_add_redir(block, tmp->data, tmp->type, data);
			tmp2 = tmp->next;
			ft_token_remouve(data, tmp);
			i++;
			tmp = tmp2;
		}
		if (tmp)
			tmp = tmp->next;
	}
	if (i > 0)
		block->heredoc_exp = 1;
	else
		block->heredoc_exp = 0;
}

void	ft_set_block(t_data *data)
{
	t_token	*tmp;
	t_block	*block;
	char	**args;
	size_t	i;

	tmp = data->token;
	while (tmp)
	{
		block = ft_block_new(data);
		i = 0;
		ft_set_redir(tmp, block, data);
		block->cmd = ft_strdup(tmp->data);
		args = ft_calloc(sizeof(char *), (clac_size_block(tmp) + 1));
		while (tmp && ft_strcmp(tmp->data, "|") != 0)
		{
			args[i++] = ft_strdup(tmp->data);
			tmp = tmp->next;
		}
		block->args = args;
		if (tmp)
			tmp = tmp->next;
	}
}
