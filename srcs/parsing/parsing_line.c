/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:49:51 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 17:58:08 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup(char *line, t_data *data)
{
	
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
	g_error = 0;
	return (0);
}
