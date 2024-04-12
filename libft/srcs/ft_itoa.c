/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:08 by mpitot            #+#    #+#             */
/*   Updated: 2023/11/13 11:36:41 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static size_t	ft_count(unsigned int n)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static void	ft_revstr(char *str, size_t j)
{
	size_t	i;
	char	temp;

	i = 0;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static void	ft_fill(char *str, unsigned int n, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		str[i] = (n % 10 + 48);
		n /= 10;
		i++;
	}
	ft_revstr(str, len - 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	size;

	if (n < 0)
	{
		size = ft_count(n * -1);
		str = ft_calloc((size + 2), sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '-';
		ft_fill(&str[1], n * -1, size);
	}
	else
	{
		size = ft_count(n);
		str = ft_calloc((size + 1), sizeof(char));
		if (!str)
			return (NULL);
		ft_fill(str, n, size);
	}
	return (str);
}
