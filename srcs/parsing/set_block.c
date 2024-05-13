/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:03:37 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/13 10:21:40 by mpitot           ###   ########.fr       */
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

void	ft_set_redir(t_token *token, t_block *block, t_data *data)
{
	t_token	*tmp;

	while (token && ft_strcmp(token->data, "|") != 0)
	{
		if (token->type >= REDIR_IN && token->type <= REDIR_HEREDOC)
		{
			ft_add_redir(block, token->data, token->type, data);
			tmp = token->next;
			if (data->token == token)
			{
				ft_token_rmfurst(data, token);
				token = data->token;
			}
			else
			{
				ft_token_remouve(data, token);
				token = tmp;
			}
		}
		else if (token)
			token = token->next;
	}
}

void	make_block(t_data *data, char **args)
{
	size_t	i;
	t_token	*tmp;

	i = 0;
	while (data->token && ft_strcmp(data->token->data, "|") != 0)
	{
		args[i++] = ft_strdup(data->token->data);
		if (!args[i - 1])
			exit_error(ERROR_MALLOC, NULL, data);
		tmp = data->token;
		data->token = data->token->next;
		free(tmp->data);
		free(tmp);
	}
}

void	ft_set_block(t_data *data)
{
	t_block	*block;
	char	**args;
    t_token *tmp;

	while (data->token)
	{
		block = ft_block_new(data);
		ft_set_redir(data->token, block, data);
		if (data->token == NULL && ft_strcmp(data->token->data, "|") == 0)
			block->cmd = NULL;
		else
		{
			block->cmd = ft_strdup(data->token->data);
			if (!block->cmd)
				exit_error(ERROR_MALLOC, NULL, data);
		}
		args = ft_calloc(sizeof(char *), (clac_size_block(data->token) + 1));
		if (!args)
			exit_error(ERROR_MALLOC, NULL, data);
		make_block(data, args);
		block->args = args;
		if (data->token)
        {
            tmp = data->token;
            data->token = data->token->next;
            free(tmp->data);
            free(tmp);
        }
	}
}
