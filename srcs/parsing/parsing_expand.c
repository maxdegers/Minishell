/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:42 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/30 16:44:38 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo $USER"$USER"'$USER'$"USER"$'USER'

void	do_expan()
{}
size_t	ft_count(t_data *data, char *s)
{
	size_t	i;

	if (s == NULL)
		exit_error(ERROR_MALLOC, NULL, data);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
{
	size_t count;

	count = 0;
	while (data)
	{
		count++;
		data = data->next;
	}
	return (count);
}

size_t	calc_expan(t_token	*token, t_data *data)
{
	size_t size;
	size_t	i;
	int		quote;


	i = 0;
	size = 0;
	quote = -1;
	while (token->data[i])
	{
		if (token->data[i] == S_QUOTE)
			quote *= -1;
		if (token->data[i] == '$' && quote != 1)
		{
			if (token->data[i + 1] == '?')
				size += ft_count(data, ft_itoa(g_error));
			else if (token->data[i + 1] == '\0')
			{
				
			}
			else
				size++;
		}
	}
}

void	ft_param_expansion(t_data *data)
{
	t_token	*tmp;

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
		   do_expan(data, tmp, calc_expan(tmp, data));
		}
		tmp = tmp->next;   
	}
}
