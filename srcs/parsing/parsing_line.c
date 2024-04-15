/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/15 12:25:42 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_set(char *line, t_data *data)
{
	size_t	i;
	size_t	end;
	size_t	start;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] != ESPACE)
		{
			start = i;
			while (line[i] && line[i] != ESPACE)
			{
				if (line[i] == '\'' || line[i] == '\"')
				{
					quote = line[i];
					i++;
					while (line[i] && line[i] != quote)
						i++;
				}
				if (line[i] == '<' || line[i] == '>')
				{
					end = i;
					ft_token_new_add(data, start, end, WORD);
					start = i;
					if (line[i + 1] != '\0' && line[i + 1] == line[i])
						i++;
					i++;
					break ;
				}
				i++;
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
	g_error = 0;
	return (0);
}
