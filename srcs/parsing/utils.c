/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:55:41 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/17 19:24:17 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_iscontrol_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_iscaracter_env(char c, int type)
{
	if (type == 0)
	{
		if (ft_isalnum(c) == 1 || c == '_')
			return (1);
	}
	else
	{
		if (ft_isalpha(c) == 1 || c == '_')
			return (1);
	}
	return (0);
}

int	ft_islineblank(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isblank(line[i++]))
			return (0);
	}
	return (1);
}