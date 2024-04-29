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

void	ft_puth1(void)
{
	printf("\n                      %s#################\n", B_RED);
	printf("                #############################\n");
	printf("             ##########%s******%s###%s******%s##########\n",
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("          ########%s**%s##%s*******%s###", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	printf("%s*******%s##%s**%s########\n", B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("        #######%s******%s##%s*******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	printf("%s*******%s###%s*****%s#######\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	printf("      ########%s*******%s##%s*******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	printf("%s*******%s##%s*******%s########\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	printf("     ######%s**%s##%s*******%s##%s******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s******%s##%s*******%s##%s**%s######\n", B_YELLOW, B_RED, B_YELLOW,
		B_RED, B_YELLOW, B_RED);
	printf("    #####%s*****%s##%s*******%s#%s******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s******%s#%s*******%s##%s*****%s#####\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("   #####%s********%s##%s*****%s##%s*****%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
}

void	ft_puth2(void)
{
	printf("%s*****%s##%s*****%s##%s********%s#####\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("  ########%s*******%s##%s*****%s#%s*****%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s*****%s#%s*****%s##%s*******%s########\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("  #####%s***%s##%s*******%s#%s*****%s#%s****%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s****%s#%s*****%s#%s*******%s##%s***%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("  #####%s*****%s##%s******%s#%s****%s#%s****%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s****%s#%s****%s#%s******%s##%s*****%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("  #####%s*******%s##%s*****%s#%s****%s#%s***%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s***%s#%s****%s#%s*****%s##%s*******%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("  #######%s********%s#%s****%s#%s***%s#%s***%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("%s***%s#%s***%s#%s****%s#%s********%s#######\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	printf("    #########%s*****%s#%s*************", B_YELLOW, B_RED,
		B_YELLOW);
	printf("**********%s#%s*****%s#########\n", B_RED, B_YELLOW, B_RED);
}

void	ft_putheader(void)
{
	ft_puth1();
	ft_puth2();
	printf("        ########%s*****************************%s########\n",
		B_YELLOW, B_RED);
	printf("           #####%s*****************************%s#####\n",
		B_YELLOW, B_RED);
	printf("            #####%s****************************%s#####\n",
		B_YELLOW, B_RED);
	printf("            #####%s***************************%s#####\n",
		B_YELLOW, B_RED);
	printf("            ######################### by mbrousse\n");
	printf("            ############################ & mpitot%s\n\n", RESET);
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
