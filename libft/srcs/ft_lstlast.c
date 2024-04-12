/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:41:01 by mpitot            #+#    #+#             */
/*   Updated: 2023/11/11 12:41:01 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*temp;

	if (!lst)
		return (0);
	i = 1;
	temp = lst;
	while (temp->next)
	{
		temp = temp->next;
		i++;
	}
	return (temp);
}
