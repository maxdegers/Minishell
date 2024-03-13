/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:08:38 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/13 20:23:20 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_signal(void)
{
    signal(SIGINT, ft_signal);
    signal(SIGQUIT, ft_signal);
}

int	ft_main_loop(t_data *data)
{
    char    *line;
    
    while (!data->exit)
    {
        set_signal();
    }
    
    return (0);
}