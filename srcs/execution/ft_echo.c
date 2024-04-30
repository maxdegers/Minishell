/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:33:15 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/12 22:45:26 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_block *block, int fd)
{
	int		nl;

	nl = 1;
	if (block->args[0] && ft_strcmp(block->args[0], "-n") == 0)
		nl = 0;
	while (*block->args)
	{
		ft_putstr_fd(*block->args, fd);
		block->args++;
		if (*block->args)
			ft_putstr_fd(" ", fd);
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	return (0);
}
