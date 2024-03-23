/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/23 13:21:40 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setpos(t_token *token)
{
	t_token	*tmp;
	size_t	pos;
	int		exec;

	tmp = token;
	pos = 0;
	exec = 0;
	while (tmp)
	{
		tmp->pos = pos;
		pos++;
		if (tmp->type == POINT_VIRGULE || tmp->type == PIPE)
		{
			exec++;
			tmp->exec = -1;
		}
		else
			tmp->exec = exec;
		tmp = tmp->next;
	}
}

static int	setup(char *line, t_data *data)
{
	size_t	i;
	int		error;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] == '\'' || line[i] == '\"' || line[i] == '|'
				|| line[i] == '>' || line[i] == '<' || line[i] == ';')
				error = puttype(line, &i, data);
			else
				error = putword(line, &i, data);
			if (error == 1)
				return (1);
		}
		else
			i++;
	}
	setpos(data->token);
	return (0);
}

static int	checkerreur(t_data *data)
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
		return (exit_error(ERROR_MALLOC, EM_MALLOC, data), 1);
	if (checkerreur(data) == 1)
		return (ft_put_error(255, "minishell: invalid pattern\n"), 1);
	data->line = line;
	g_error = 0;
	return (0);
}
