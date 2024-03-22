/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:22:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 14:11:31 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_type(char c)
{
	if (c == '\'')
		return (SIMPLE_COTE);
	else if (c == '"')
		return (DOUBLE_COTE);
	else if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (REDIR_R);
	else if (c == '<')
		return (REDIR_L);
	else
		return (CMD);
}

int	putcote(char *line, size_t *i, t_data *data)
{
	char	*tmp;
	t_type	type;

	tmp = ft_substr(line, *i, 1);
	if (!tmp)
	{
		g_error = ERROR_GERROR;
		return (1);
	}
	(*i)++;
	type = get_type(tmp[0]);
	lt_addback(&data->token, lt_new(tmp, type));
	free(tmp);
	return (0);
}

int	putpipe(char *line, size_t *i, t_data *data)
{
	char	*tmp;

	tmp = ft_substr(line, *i, 1);
	if (!tmp)
	{
		g_error = ERROR_GERROR;
		return (1);
	}
	(*i)++;
	lt_addback(&data->token, lt_new(tmp, PIPE));
	free(tmp);
	return (0);
}

int	putredirection(char *line, size_t *i, t_data *data)
{
	char	*tmp;
	t_type	type;

	tmp = ft_substr(line, *i, 1);
	if (!tmp)
	{
		g_error = ERROR_GERROR;
		return (1);
	}
	(*i)++;
	type = get_type(tmp[0]);
	lt_addback(&data->token, lt_new(tmp, type));
	free(tmp);
	return (0);
}

void	putword_move(char *line, size_t *i, int t)
{
	if (t == 1)
	{
		while (line[*i] && line[*i] != ' '
			&& line[*i] != '\'' && line[*i] != '"'
			&& line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
			(*i)++;
	}
	else
	{
		while (line[*i] && line[*i] != '\'' && line[*i] != '"'
			&& line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
			(*i)++;
	}
}

int	putword(char *line, size_t *i, t_data *data)
{
	size_t	j;
	char	*tmp;
	t_type	type;

	j = *i;
	if (get_type(line[j - 1]) == DOUBLE_COTE || get_type(line[j - 1]) == SIMPLE_COTE)
	{
		putword_move(line, &j, 0);
		type = STRING;
	}
	else
	{
		putword_move(line, &j, 1);
		type = CMD; 
	}
	tmp = ft_substr(line, *i, j - *i);
	if (!tmp)
	{
		g_error = ERROR_GERROR;
		return (1);
	}
	lt_addback(&data->token, lt_new(tmp, type));
	free(tmp);
	*i = j;
	return (0);
}
