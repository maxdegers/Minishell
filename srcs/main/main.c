/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:20:57 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/22 13:27:49 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putheader(void)
{
	ft_printf("\n\n"HEADER);
	ft_printf("________     _____              _________ ___ ______");
	ft_printf("________.____    .____\n");
	ft_printf("\\_____  \\   /     \\            /   _____//   |   ");
	ft_printf("\\_   _____/|    |   |    |\n");
	ft_printf("  _(__  <  /  \\ /  \\   ______  \\_____  \\/    ~    ");
	ft_printf("\\    __)_ |    |   |    |\n");
	ft_printf(" /       \\/    Y    \\ /_____/  /        \\    Y    /");
	ft_printf("        \\|    |___|    |___\n");
	ft_printf("/______  /\\____|__  /         /_______  /\\___|_  /");
	ft_printf("_______  /|_______ \\_______ \\\n");
	ft_printf("       \\/         \\/                  \\/       \\");
	ft_printf("/        \\/         \\/       \\/\n\n\n"RESET);
}

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
