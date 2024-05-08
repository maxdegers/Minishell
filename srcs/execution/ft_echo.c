/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:33:15 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/02 14:23:08 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_block *block)
{
	int		nl;
	size_t	i;

	nl = 1;
	i = 1;
	if (block->args[1] && ft_strcmp(block->args[1], "-n") == 0)
	{
		nl = 0;
		i++;
	}
	while (block->args[i])
	{
		ft_putstr_fd(block->args[i], 1);
		i++;
		if (block->args[i])
			ft_putstr_fd(" ", 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
}
