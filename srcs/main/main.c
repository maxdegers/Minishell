/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:20:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/29 15:00:19 by mpitot           ###   ########.fr       */
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
//	close(0);
//	close(1);
//	close(2);
	return (0);
}
