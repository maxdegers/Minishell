/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:03:37 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/20 01:53:49 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	clac_size_block(t_token *token)
{
	size_t	size;
	t_token	*tmp;

	size = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

static void	ft_set_redir(t_token *token, t_block *block, t_data *data)
{
	t_token	*tmp;

	while (token && ft_strcmp(token->data, "|") != 0)
	{
		if (token->type >= REDIR_IN && token->type <= REDIR_HEREDOC)
		{
			ft_add_redir(block, token, data);
			tmp = token->next;
			if (data->token == token)
			{
				ft_token_rmfirst(data, token);
				token = data->token;
			}
			else
			{
				ft_token_remove(data, token);
				token = tmp;
			}
		}
		else if (token)
			token = token->next;
	}
}

static int	make_block(t_data *data, t_block	*block)
{
	char	**args;
	size_t	i;
	t_token	*tmp;

	args = ft_calloc(sizeof(char *), (clac_size_block(data->token) + 1));
	if (!args)
		exit_error(ERROR_MALLOC, NULL, data);
	block->args = args;
	i = 0;
	while (data->token && data->token->type != PIPE)
	{
		args[i++] = ft_strdup(data->token->data);
		if (!args[i - 1])
			exit_error(ERROR_MALLOC, NULL, data);
		tmp = data->token;
		data->token = data->token->next;
		free(tmp->data);
		free(tmp);
	}
	return (1);
}

void	ft_set_block(t_data *data)
{
	t_block	*block;
	t_token	*tmp;

	while (data->token)
	{
		block = ft_block_new(data);
		ft_set_redir(data->token, block, data);
		if (data->token == NULL)
			block->cmd = NULL;
		else if (data->token->type == PIPE)
			block->cmd = NULL;
		else
		{
			block->cmd = ft_strdup(data->token->data);
			if (!block->cmd)
				exit_error(ERROR_MALLOC, NULL, data);
		}
		if (make_block(data, block) && data->token)
		{
			tmp = data->token;
			data->token = data->token->next;
			free(tmp->data);
			free(tmp);
		}
	}
}
