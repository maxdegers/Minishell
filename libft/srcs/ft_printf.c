/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:16:37 by mpitot            #+#    #+#             */
/*   Updated: 2024/02/12 17:43:00 by mpitot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"

static int	ft_recurs(uintptr_t n, const char *base)
{
	int		x;
	int		y;

	if (n < 16)
		return (ft_putchar(base[n]));
	x = ft_recurs(n / 16, base);
	if (x == -1)
		return (-1);
	y = ft_putchar(base[n % 16]);
	if (y == -1)
		return (-1);
	return (x + y);
}

int	ft_putmem(void *ptr)
{
	int		x;
	int		y;

	if (!ptr)
		return (ft_putstr("(nil)"));
	x = ft_putstr("0x");
	if (x == -1)
		return (-1);
	y = ft_recurs(((uintptr_t) ptr), "0123456789abcdef");
	if (y == -1)
		return (-1);
	return (x + y);
}

static int	ft_convert(char c, va_list args)
{
	if (!c)
		return (-1);
	if (c == '%')
		return (ft_putchar('%'));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_putnbr_u(va_arg(args, unsigned int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 'x')
		return (ft_putnbr_x(va_arg(args, int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putnbr_x(va_arg(args, int), "0123456789ABCDEF"));
	if (c == 'p')
		return (ft_putmem(va_arg(args, void *)));
	return (ft_putchar('%') + ft_putchar(c));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		res;
	int		temp;

	if (!format || write(1, 0, 0) == -1)
		return (-1);
	va_start(args, format);
	i = 0;
	res = 0;
	while (format[i])
	{
		if (format[i] == '%')
			temp = ft_convert(format[++i], args);
		else
			temp = ft_putchar(format[i]);
		if (temp == -1)
			return (-1);
		res += temp;
		i++;
	}
	va_end(args);
	return (res);
}
