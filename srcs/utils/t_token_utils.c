/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:55:13 by mbrousse          #+#    #+#             */
/*   Updated: 2024/03/30 13:55:54 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lt_to_tab(t_token *token)
{
	char	**tab;
	size_t	i;

	i = 0;
	tab = malloc(sizeof(char *) * (lt_size(token) + 1));
	if (!tab)
		return (NULL);
	while (token)
	{
		tab[i] = ft_strdup(token->value);
		if (!tab[i])
			return (ft_free_tab(tab), NULL);
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
