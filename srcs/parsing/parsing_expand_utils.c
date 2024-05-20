/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:44:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/18 21:04:57 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	calc_expan_size(t_token	*token, t_data *data, size_t *size, size_t *i)
{
	char	*tmp;

	if (token->data[*i + 1] == '?')
	{
		tmp = ft_itoa(g_error);
		*size += ft_count(data, tmp, 0);
		free(tmp);
		*i += 1;
	}
	else if (ft_iscaracter_env(token->data[*i + 1], 0) == 1
		&& token->data[*i + 1] != '\0' && token->data[*i + 1] != D_QUOTE
		&& token->data[*i + 1] != SPACE)
		ft_cal_expand_utils(i, size, token->data, data);
	else if (ft_check_is_incote(token->data, i) == 1
		|| token->data[*i + 1] == '\0'
		|| ft_iscaracter_env(token->data[*i + 1], 0) == 0)
		*size += 1;
}

static size_t	calc_expan(t_token	*token, t_data *data, int quote)
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

size_t	ft_count(t_data *data, char *s, int type)
{
	size_t	i;

	if (s == NULL && type == 0)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
