/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:20:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/05/14 14:03:29 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	g_error = 0;
	if (argc > 1)
		return (ft_put_error(1, EM_ARGS), 1);
	if (isatty(STDOUT_FILENO))
		ft_putheader();
	if (ft_init_tab(&data, env))
		return (ft_megafree(&data), 1);
	if (ft_main_loop(&data))
		return (ft_megafree(&data), 1);
	ft_megafree(&data);
	return (0);
}
