/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:16:21 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:19:22 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_checktype_printf(char c, va_list *args, int *len)
{
	if (c == 0)
		return ;
	if (c == 'c')
		ft_putchar_printf(va_arg((*args), int), len);
	else if (c == 's')
		ft_putstr_printf(va_arg((*args), char *), len);
	else if (c == 'p')
		ft_putptr_printf(va_arg((*args), unsigned long int), len);
	else if (c == 'i' || c == 'd')
		ft_putnbr_printf(va_arg((*args), int), len);
	else if (c == 'u')
		ft_putnbr_unsigned_printf(va_arg((*args), unsigned int), len);
	else if (c == 'x' || c == 'X')
		ft_puthex_printf(va_arg((*args), unsigned long int), c, len);
	else if (c == '%')
		ft_putchar_printf('%', len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	if (!str)
		return (-1);
	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ft_checktype_printf(str[i], &args, &len);
		}
		else
			ft_putchar_printf(str[i], &len);
		i++;
	}
	va_end(args);
	return (len);
}
