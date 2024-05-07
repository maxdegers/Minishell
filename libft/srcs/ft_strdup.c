/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:21:50 by mpitot            #+#    #+#             */
/*   Updated: 2024/05/07 14:43:45 by mbrousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	new = ft_calloc(sizeof(char), (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i])
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strdup_size(const char *s, size_t size)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	if (size == 0)
	{
		new = malloc(sizeof(char) * 2);
		if (!new)
			return (NULL);
		new[0] = s[0];
		new[1] = '\0';
		return (new);
	}
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s[++i] && i < size)
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
