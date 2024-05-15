/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:49:49 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/15 10:49:09 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_type(t_token *token)
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

void	set_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		put_type(tmp);
		tmp = tmp->next;
	}
}

int	puterror_check_redir(t_token *tmp)
{
	if (tmp->type == 1)
	{
		
	}
	else if (tmp->next == NULL || tmp->next->type != WORD)
	{
		if (tmp->type == 1 && tmp->type == tmp->next->type)
			ft_printf_fd(2, "minishell: syntax error near\
unexpected token `%s'\n", tmp->next->data);
		else if (tmp->next == NULL)
			ft_printf_fd(2, "minishell: syntax error\
near unexpected token `newline'\n");
		else
			ft_printf_fd(2, "minishell: syntax error near\
unexpected token `%s'\n", tmp->next->data);
		return (1);
	}
}

int	check_redir(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type > 0 && tmp->type < 6)
		{
			if (puterror_check_redir(tmp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_redir_expansion(t_data *data)
{
	t_token	*token;
	t_token	*tmp;

	set_type(data);
	if (check_redir(data) == 1)
		return (1);
	token = data->token;
	while (token)
	{
		if ((token->type > 1 && token->type < 6) && token->next->type == WORD)
		{
			tmp = token->prev;
			token = token->next;
			token->type = token->prev->type;
			if (!tmp)
			{
				ft_token_rmfurst(data, token->prev);
				token = data->token;
			}
			else
				ft_token_remouve(data, tmp->next);
		}
		token = token->next;
	}
	return (0);
}
