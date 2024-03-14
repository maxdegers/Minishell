/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:17:27 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/14 10:06:42 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_signal(void)
{
	signal(SIGINT, ft_handle_sig);
}

void	ft_handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_error = 130;
		ft_printf("SIGINT catched\n");
	}
}
