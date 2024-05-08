/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:55:13 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/08 12:05:18 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_token_size(t_token *token)
{
	size_t	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

char	**ft_tokento_tab(t_token *token)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_token_size(token) + 1));
	if (!tab)
		return (NULL);
	while (token)
	{
		tab[i] = ft_strdup(token->data);
		if (!tab[i])
			return (ft_free_tab(tab), NULL);
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	ft_token_remouve(t_data *data, t_token *to_remouve)
{
	t_token	*tmp;

	if (!data->token || !to_remouve)
		return ;
	if (data->token == to_remouve)
		ft_token_rmfurst(data, to_remouve);
	tmp = data->token;
	while (tmp->next)
	{
		if (tmp->next == to_remouve)
		{
			tmp->next = to_remouve->next;
			free(to_remouve->data);
			free(to_remouve);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_token_rmfurst(t_data *data, t_token *to_remouve)
{
	t_token	*tmp;

	if (!data->token || !to_remouve)
		return ;
	if (data->token == to_remouve)
	{
		if (!data->token->next)
		{
			free(data->token->data);
			free(data->token);
			data->token = NULL;
			return ;
		}
		tmp = data->token->next;
		free(data->token->data);
		free(data->token);
		data->token = tmp;
		data->token->prev = NULL;
		return ;
	}
}

void	ft_token_rm_redir(t_data *data, t_token *to_remouve)
{
	t_token	*tmp;

	if (!data->token || !to_remouve)
		return ;
	tmp = data->token;
	while (tmp->next)
	{
		if (tmp->next == to_remouve)
		{
			tmp->next = to_remouve->next;
			to_remouve->next->prev = tmp;
			free(to_remouve->data);
			free(to_remouve);
			return ;
		}
		tmp = tmp->next;
	}
}
