/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babischa <babischa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:39:45 by babischa          #+#    #+#             */
/*   Updated: 2024/11/27 14:06:33 by babischa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_str(char *s, int fd)
{
	if (s == NULL)
		write(1, "(null)", 6);
	else
	{
		while (*s)
			ft_putchar_fd(*s++, fd);
	}
}

void	ft_type(char token, va_list args, int fd)
{
	if (token == 'c')
		ft_putchar_fd(va_arg(args, int), fd);
	else if (token == 's')
		ft_printf_str(va_arg(args, char *), fd);
}

void	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;

	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
			ft_type((*++str), args, fd);
		else
			ft_putchar_fd(*str, fd);
		str++;
	}
	va_end(args);
}
