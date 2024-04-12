/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:34:04 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/13 15:34:04 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

int	ft_putchar_fd_int(int c, int fd)
{
	return ((int) write(fd, &c, 1));
}

int	ft_putnbr_u_fd(unsigned int n, int fd)
{
	int		x;
	int		y;

	if (n < 10)
		return (ft_putchar_fd_int((int) n + 48, fd));
	x = ft_putnbr_u_fd(n / 10, fd);
	if (x == -1)
		return (-1);
	y = ft_putchar_fd_int(((int)(n % 10) + 48), fd);
	if (y == -1)
		return (-1);
	return (x + y);
}

int	ft_putnbr_fd_int(int n, int fd)
{
	int		x;
	int		y;

	if (n < 0)
	{
		x = ft_putchar_fd_int('-', fd);
		if (x == -1)
			return (-1);
		y = ft_putnbr_u_fd(n * -1, fd);
		if (y == -1)
			return (-1);
		return (x + y);
	}
	else
		return (ft_putnbr_u_fd(n, fd));
}

int	ft_putnbr_x_fd(unsigned int nbr, char *base, int fd)
{
	int		x;
	int		y;

	if (nbr < 16)
		return (ft_putchar_fd_int(base[nbr], fd));
	x = ft_putnbr_x_fd(nbr / 16, base, fd);
	if (x == -1)
		return (-1);
	y = ft_putchar_fd_int(base[nbr % 16], fd);
	if (y == -1)
		return (-1);
	return (x + y);
}

int	ft_putstr_fd_int(const char *s, int fd)
{
	if (!s)
		return (ft_putstr("(null)"));
	return ((int) write(fd, s, ft_strlen(s)));
}
