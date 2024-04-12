/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pac.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:24:28 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/28 15:27:58 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

void	ft_free_pac(size_t count, ...)
{
	va_list	args;
	size_t	i;

	va_start(args, count);
	i = 0;
	while (i < count)
	{
		free(va_arg(args, void *));
		i++;
	}
	va_end(args);
}
