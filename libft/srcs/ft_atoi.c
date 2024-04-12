/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:23:19 by mpitot            #+#    #+#             */
/*   Updated: 2023/11/08 17:29:41 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_checker(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	if (c >= '0' && c <= '9')
		return (2);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				value;
	int				sign;

	i = 0;
	value = 0;
	sign = 1;
	while (ft_checker(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (ft_checker(nptr[i]) == 2)
	{
		value = value * 10 + nptr[i] - 48;
		i++;
	}
	return (value * sign);
}
