/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:26:54 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:19:07 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_printf(int n, int *len)
{
	int		sign;
	char	c;

	sign = 1;
	if (n < 0)
	{
		ft_putchar_printf('-', len);
		sign = -1;
	}
	if (n / 10)
		ft_putnbr_printf(n / 10 * sign, len);
	c = '0' + n % 10 * sign;
	ft_putchar_printf(c, len);
}

void	ft_putnbr_unsigned_printf(unsigned int n, int *len)
{
	if (n <= 9)
		ft_putchar_printf(n + 48, len);
	else
	{
		ft_putnbr_unsigned_printf(n / 10, len);
		ft_putchar_printf((n % 10) + 48, len);
	}
}

void	ft_puthex_printf(unsigned int number, int flag, int *len)
{
	if (number >= 16)
	{
		ft_puthex_printf((number / 16), flag, len);
		ft_puthex_printf((number % 16), flag, len);
	}
	else
	{
		if (flag == 'x')
			ft_putchar_printf(HEX_LOWCASE[number], len);
		else
			ft_putchar_printf(HEX_UPCASE[number], len);
	}
}

void	ft_puthex_address_printf(unsigned long int number, int flag, int *len)
{
	if (number >= 16)
	{
		ft_puthex_address_printf((number / 16), flag, len);
		ft_puthex_address_printf((number % 16), flag, len);
	}
	else
	{
		if (flag == 'x')
			ft_putchar_printf(HEX_LOWCASE[number], len);
		else
			ft_putchar_printf(HEX_UPCASE[number], len);
	}
}

void	ft_putptr_printf(unsigned long int ptr, int *len)
{
	if (!ptr)
		ft_putstr_printf("(nil)", len);
	else
	{
		ft_putstr_printf("0x", len);
		ft_puthex_address_printf(ptr, 'x', len);
	}
}
