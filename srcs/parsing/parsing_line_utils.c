/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:22:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/27 17:14:09 by mbrousse         ###   ########.fr       */
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
		return (OUTPUT);
	else if (c == '<')
		return (INPUT);
	else if (c == ';')
		return (POINT_VIRGULE);
	else
		return (WORD);
}

int	puttype_s(char *line, t_type *type, size_t *i, char **tmp)
{
	if ((line[*i] == '>' && line[*i + 1] == '>')
		|| (line[*i] == '<' && line[*i + 1] == '<'))
	{
		*tmp = ft_substr(line, *i, 2);
		if (line[*i] == '>')
			*type = APPEND;
		else
			*type = HEREDOC;
	}
	else
	{
		*tmp = ft_substr(line, *i, 1);
		*type = get_type(tmp[0][0]);
	}
	if (!tmp)
		return (1);
	return (0);
}

int	puttype(char *line, size_t *i, t_data *data)
{
	char	*tmp;
	t_type	type;
	t_token	*token;

	if (puttype_s(line, &type, i, &tmp) == 1)
		return (1);
	*i += ft_strlen(tmp);
	token = lt_new(tmp, type);
	if (!token)
		return (free(tmp), 1);
	lt_addback(&data->token, token);
	return (free(tmp), 0);
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
	if (j == 0)
		type = WORD;
	else
	{
		if (get_type(line[j - 1]) == DOUBLE_COTE
			|| get_type(line[j - 1]) == SIMPLE_COTE)
			type = STRING;
		else
			type = WORD;
	}
	if (type == WORD)
		putword_move(line, &j, 1);
	else
		putword_move(line, &j, 0);
	tmp = ft_substr(line, *i, j - *i);
	if (!tmp)
		return (free(tmp), 1);
	lt_addback(&data->token, lt_new(tmp, type));
	*i = j;
	return (free(tmp), 0);
}
