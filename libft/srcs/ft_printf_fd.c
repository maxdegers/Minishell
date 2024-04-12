/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:30:12 by mpitot            #+#    #+#             */
/*   Updated: 2024/03/13 15:54:44 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_recurs(uintptr_t n, const char *base, int fd)
{
	int		x;
	int		y;

	if (n < 16)
		return (ft_putchar(base[n]));
	x = ft_recurs(n / 16, base, fd);
	if (x == -1)
		return (-1);
	y = ft_putchar_fd_int(base[n % 16], fd);
	if (y == -1)
		return (-1);
	return (x + y);
}

int	ft_putmem_fd(void *ptr, int fd)
{
	int		x;
	int		y;

	if (!ptr)
		return (ft_putstr("(nil)"));
	x = ft_putstr("0x");
	if (x == -1)
		return (-1);
	y = ft_recurs(((uintptr_t) ptr), "0123456789abcdef", fd);
	if (y == -1)
		return (-1);
	return (x + y);
}

static int	ft_convert(char c, va_list args, int fd)
{
	if (!c)
		return (-1);
	if (c == '%')
		return (ft_putchar_fd_int('%', fd));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd_int(va_arg(args, int), fd));
	if (c == 'u')
		return (ft_putnbr_u_fd(va_arg(args, unsigned int), fd));
	if (c == 's')
		return (ft_putstr_fd_int(va_arg(args, char *), fd));
	if (c == 'c')
		return (ft_putchar_fd_int(va_arg(args, int), fd));
	if (c == 'x')
		return (ft_putnbr_x_fd(va_arg(args, int), "0123456789abcdef", fd));
	if (c == 'X')
		return (ft_putnbr_x_fd(va_arg(args, int), "0123456789ABCDEF", fd));
	if (c == 'p')
		return (ft_putmem_fd(va_arg(args, void *), fd));
	return (ft_putchar_fd_int('%', fd) + ft_putchar_fd_int(c, fd));
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		res;
	int		temp;

	if (!format || write(fd, 0, 0) == -1)
		return (-1);
	va_start(args, format);
	i = 0;
	res = 0;
	while (format[i])
	{
		if (format[i] == '%')
			temp = ft_convert(format[++i], args, fd);
		else
			temp = ft_putchar_fd_int(format[i], fd);
		if (temp == -1)
			return (-1);
		res += temp;
		i++;
	}
	va_end(args);
	return (res);
}
