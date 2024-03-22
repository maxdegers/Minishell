/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:22:35 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 13:38:28 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (tmp[0] == '\'')
		type = SIMPLE_COTE;
	else
		type = DOUBLE_COTE;
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
	if (tmp[0] == '>')
		type = REDIR_R;
	else
		type = REDIR_L;
	lt_addback(&data->token, lt_new(tmp, type));
	free(tmp);
	return (0);
}

int	putword(char *line, size_t *i, t_data *data)
{
	size_t	j;
	char	*tmp;
	t_type	type;

	j = *i;
	while (line[j] && line[j] != ' ' && line[j] != '\'' && line[j] != '\"'
		&& line[j] != '|' && line[j] != '>' && line[j] != '<')
		j++;
	tmp = ft_substr(line, *i, j - *i);
	if (!tmp)
	{
		g_error = ERROR_GERROR;
		return (1);
	}
	if (line[*i] == '\"')
		type = STRING;
	else if (line[*i] == '\'')
		type = STRING;
	else
		type = CMD;
	lt_addback(&data->token, lt_new(tmp, type));
	free(tmp);
	*i = j;
	return (0);
}
