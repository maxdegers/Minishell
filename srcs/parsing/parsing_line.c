/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 15:26:51 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup(char *line, t_data *data)
{
	size_t	i;
	int		error;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] == '\'' || line[i] == '\"')
				error = putcote(line, &i, data);
			else if (line[i] == '|')
				error = putpipe(line, &i, data);
			else if (line[i] == '>' || line[i] == '<')
				error = putredirection(line, &i, data);
			else
				error = putword(line, &i, data);
			if (error == 1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	checherreur(t_data *data)
{
	size_t	count;
	t_token	*tmp;

	count = 0;
	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == SIMPLE_COTE || tmp->type == DOUBLE_COTE)
			count++;
		tmp = tmp->next;
	}
	if (count % 2 != 0)
		return (1);
	return (0);
}

int	ft_parsing_line(t_data *data, char *line)
{
	if (setup(line, data) == 1)
		return (ft_put_error(1, EM_MALLOC), 1);
	if (checherreur(data) == 1)
		return (ft_put_error(128, NULL), 1);
	data->line = line;
	g_error = 0;
	return (0);
}
