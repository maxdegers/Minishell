/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:19:19 by mbrousse          #+#    #+#             */
/*   Updated: 2024/04/12 13:24:07 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_trash	*ft_trashnew(void *content)
{
	t_trash	*new;

	new = malloc(sizeof(t_trash));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_trashadd_back(t_trash **lst, t_trash *new)
{
	t_trash	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_trashclear(t_trash **lst)
{
	t_trash	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->data);
		free(*lst);
		*lst = tmp;
	}
}
