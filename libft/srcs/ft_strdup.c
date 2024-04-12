/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:21:50 by mpitot            #+#    #+#             */
/*   Updated: 2023/11/10 13:54:40 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i])
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
