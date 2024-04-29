/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satanast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:12:05 by mpitot            #+#    #+#             */
/*   Updated: 2024/04/29 15:13:41 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_puth1(void)
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

static void	ft_puth2(void)
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
