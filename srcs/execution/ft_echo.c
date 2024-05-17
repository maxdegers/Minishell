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

int	ft_is_flag(char *arg)
{
	size_t	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

void	ft_echo(t_block *block)
{
	int		nl;
	size_t	i;

	nl = 1;
	i = 1;
	if (block->args[1] && ft_is_flag(block->args[1]))
	{
		nl = 0;
		i++;
	}
	while (block->args[i])
	{
		ft_printf("%s", block->args[i]);
		i++;
		if (block->args[i])
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
}
