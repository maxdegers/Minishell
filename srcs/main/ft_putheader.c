/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putheader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:12:05 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/19 23:49:54 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_puth1(void)
{
	ft_printf("\n                      %s#################\n", B_RED);
	ft_printf("                #############################\n");
	ft_printf("             ##########%s******%s###%s******%s##########\n",
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("          ########%s**%s##%s*******%s###", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	ft_printf("%s*******%s##%s**%s########\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED);
	ft_printf("        #######%s******%s##%s*******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	ft_printf("%s*******%s###%s*****%s#######\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	ft_printf("      ########%s*******%s##%s*******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	ft_printf("%s*******%s##%s*******%s########\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED);
	ft_printf("     ######%s**%s##%s*******%s##%s******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s******%s##%s*******%s##%s**%s######\n",
		B_YELLOW, B_RED, B_YELLOW,
		B_RED, B_YELLOW, B_RED);
	ft_printf("    #####%s*****%s##%s*******%s#%s******%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s******%s#%s*******%s##%s*****%s#####\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
}

static void	ft_puth2(void)
{
	ft_printf("   #####%s********%s##%s*****%s##%s*****%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s*****%s##%s*****%s##%s********%s#####\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("  ########%s*******%s##%s*****%s#%s*****%s#", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s*****%s#%s*****%s##%s*******%s########\n", B_YELLOW, B_RED,
		B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("  #####%s***%s##%s*******%s#%s*****%s#%s****%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s****%s#%s*****%s#%s*******%s##%s***%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("  #####%s*****%s##%s******%s#%s****%s#%s****%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s****%s#%s****%s#%s******%s##%s*****%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("  #####%s*******%s##%s*****%s#%s****%s#%s***%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s***%s#%s****%s#%s*****%s##%s*******%s#####\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("  #######%s********%s#%s****%s#%s***%s#%s***%s#", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
	ft_printf("%s***%s#%s***%s#%s****%s#%s********%s#######\n", B_YELLOW,
		B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED, B_YELLOW, B_RED);
}

void	ft_putheader(void)
{
	ft_puth1();
	ft_puth2();
	ft_printf("    #########%s*****%s#%s*************", B_YELLOW, B_RED,
		B_YELLOW);
	ft_printf("**********%s#%s*****%s#########\n", B_RED, B_YELLOW, B_RED);
	ft_printf("        ########%s*****************************%s########\n",
		B_YELLOW, B_RED);
	ft_printf("           #####%s*****************************%s#####\n",
		B_YELLOW, B_RED);
	ft_printf("            #####%s****************************%s#####\n",
		B_YELLOW, B_RED);
	ft_printf("            #####%s***************************%s#####\n",
		B_YELLOW, B_RED);
	ft_printf("            ######################### %sby %smbrousse\n",
		RED, U_RED);
	ft_printf("%s            %s############################ %s%s& \
%smpitot%s\n\n",
		RESET, B_RED, RESET, RED, U_RED, RESET);
}
