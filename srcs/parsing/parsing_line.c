/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/18 11:31:56 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checker_set(char *line, size_t *i);

int	ft_checker_rec(char *line, size_t *i, char open, char close)
{
	size_t	j;
	size_t	k;

	j = *i;
	k = 0;
	while (line[j] != '\0')
	{
		if (line[j] == open)
			k++;
		else if (line[j] == close)
			k--;
		if (k == 0)
		{
			*i = j +1;
			return (0);
		}
		if (line[j] != open && line[j] != close)
		{
			*i = j;
			if (ft_checker_set(line, i) == 1)
				return (1);
		}
		j++;
	}
	return (1);
}

int	ft_checker_set(char *line, size_t *i)
{
	char	open;
	char	close;

	if (line[*i] == '\0')
		return (0);
	else if (line[*i] == '\"' )
	{
		open = '\"';
		close = '\"';
	}
	else if (line[*i] == '\'')
	{
		open = '\'';
		close = '\'';
	}
	else if (line[*i] == '(')
	{
		open = '(';
		close = ')';
	}
	else if (line[*i] == '{')
	{
		open = '{';
		close = '}';
	}
	else if (line[*i] == '[')
	{
		open = '[';
		close = ']';
	}
	else
		return (0);
	return (ft_checker_rec(line, i, open, close));
}

static int	checker(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_checker_set(line, &i) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_parsing_line(t_data *data, char *line)
{
	if (checker(line) == 1)
		return (1);
	ft_printf("---------\n");
	data->line = ft_strdup(line);
	return (0);
}
