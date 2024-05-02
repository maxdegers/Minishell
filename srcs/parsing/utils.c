/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:55:41 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/02 16:07:08 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isblank(char c)
{
	if (c == SPACE || c == TAB)
		return (1);
	return (0);
}

int	ft_iscontrol_operator(char c)
{
	if (c == '|' || c == ';' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_iscaracter_env(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}
