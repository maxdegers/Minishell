/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:44:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/15 15:34:37 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	calc_expan_size(t_token	*token, t_data *data, size_t *size, size_t *i)
{
	size_t	start;
	size_t	end;
	char	*tmp;

	if (token->data[*i + 1] == '?')
	{
		tmp = ft_itoa(g_error);
		*size += ft_count(data, tmp, 0);
		free(tmp);
		*i += 1;
	}
	else if (ft_iscaracter_env(token->data[*i + 1]) == 1
		|| token->data[*i + 1] != '\0')
	{
		*i += 1;
		start = *i;
		while (token->data[*i] && ft_iscaracter_env(token->data[*i]) == 1)
			*i += 1;
		end = *i;
		tmp = ft_strdup_size(&token->data[start], end - start);
		*size += ft_count(data, ft_envfind_data(data->env, tmp), 1);
		free(tmp);
		*i -= 1;
	}
}

size_t	calc_expan(t_token	*token, t_data *data, int quote)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (token->data[i] != '\0')
	{
		if (token->data[i] == S_QUOTE)
			quote *= -1;
		if (token->data[i] == '$' && quote != 1)
		{
			calc_expan_size(token, data, &size, &i);
		}
		else
			size++;
		i++;
	}
	return (size);
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;
	int		quote;

	quote = -1;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == REDIR_HEREDOC)
		{
			tmp = tmp->next;
			continue ;
		}
		else
		{
			do_expan(data, tmp, calc_expan(tmp, data, quote), quote);
		}
		tmp = tmp->next;
	}
}
