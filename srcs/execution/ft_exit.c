/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:25:17 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/13 18:53:43 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isnumber(char *s)
{
	size_t	i;

	i = -1;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

void	ft_exit(t_data *data, t_block *block)
{
	if (!block->next)
		ft_printf_fd(2, "exit\n");
	if (block->args[1] && ft_isnumber(block->args[1]))
	{
		if (block->args[2])
		{
			ft_printf_fd(2, "minishell: exit: too many arguments\n");
			g_error = 1;
			return ;
		}
		ft_megafree(data);
		exit(ft_atoi(block->args[1]) % 256);
	}
	if (block->args[1])
	{
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n", block->args[1]);
		ft_megafree(data);
		exit(2);
	}
	ft_megafree(data);
	exit(0);
}