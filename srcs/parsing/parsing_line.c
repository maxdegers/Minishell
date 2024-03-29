/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/29 11:00:47 by mbrousse         ###   ########.fr       */
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
			tmp->pos = -1;
			pos = 0;
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
	data->token = NULL;
	data->line = line;
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
		if (line[i] == ';' && (s_quote == true || d_quote == true))
			return (1);
		if (line[i] == '|' && (s_quote == true || d_quote == true))
			return (1);
		i++;
	}
	if (s_quote == true || d_quote == true)
		return (1);
	return (0);
}

int	ft_parsing_line(t_data *data, char *line)
{
	if (setup(line, data) == 1)
		return (exit_error(ERROR_MALLOC, EM_MALLOC, data), 1);
	if (checkerreur(line) == 1)
		return (ft_put_error(255, "minishell: invalid pattern\n"), 1);
	if (set_cmd_type(data) == 1)
		return (1);
	if (rm_type(data) == 1)
		return (1);
	g_error = 0;
	return (0);
}
