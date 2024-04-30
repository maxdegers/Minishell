/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:25:17 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/15 12:34:56 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isnumber(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	ft_exit(t_data *data, t_block *block)
{
	if (block->args[0])
	{
		if (block->args[1])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			g_error = 1;
			return (0);
		}
		if (ft_isnumber(block->args[1]))
			g_error = ft_atoi(block->args[1]) % 256;
		else
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(block->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_error = 2;
			return (0);
		}
	}
	ft_putstr_fd("exit\n", 2);
	ft_megafree(data);
	exit(g_error);
}
