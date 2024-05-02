/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/01 13:31:20 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parsing_line(t_data *data, size_t *i, size_t *start, size_t *end)
{
	char	quote;

	if (data->line[*i] == '\'' || data->line[*i] == '\"')
	{
		quote = data->line[*i];
		*i += 1;
		while (data->line[*i] && data->line[*i] != quote)
			*i += 1;
	}
	if (ft_iscontrol_operator(data->line[*i]) == 1)
	{
		if (*i != 0 && data->line[*i - 1] != ' ' && *start != *i)
		{
			*end = *i;
			ft_token_new_add(data, *start, *end, WORD);
			*start = *i;
		}
		if (data->line[*i + 1] != '\0' && data->line[*i + 1] == data->line[*i])
			*i += 1;
		*i += 1;
		return (1);
	}
	*i += 1;
	return (0);
}

void	ft_token_set(char *line, t_data *data)
{
	size_t	i;
	size_t	end;
	size_t	start;

	i = 0;
	while (line[i])
	{
		if (ft_isblank(line[i]) == 0)
		{
			start = i;
			while (line[i] && !ft_isblank(line[i]))
			{
				if (parsing_line(data, &i, &start, &end) == 1)
					break ;
			}
			end = i;
			ft_token_new_add(data, start, end, WORD);
		}
		else
			i++;
	}
}

static int	checkerreur(char *line)
{
	size_t	i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		if (line[i] == '\'' && d_quote == false)
			s_quote = !s_quote;
		if (line[i] == '\"' && s_quote == false)
			d_quote = !d_quote;
		i++;
	}
	if (s_quote == true || d_quote == true)
		return (1);
	return (0);
}

int	ft_parsing_line(t_data *data, char *line)
{
	data->line = line;
	if (checkerreur(line) == 1)
		return (ft_put_error(255, "minishell: invalid pattern\n"), 1);
	ft_token_set(line, data);
	if (ft_redir_expansion(data) == 1)
		return (1);
//	ft_tokenprint(data->token);
//	printf("\n\n");
	ft_param_expansion(data);
//	ft_tokenprint(data->token);
	ft_set_block(data);
	// ft_block_print(data->block);
	g_error = 0;
	return (0);
}
