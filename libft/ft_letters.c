/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_letters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:47:48 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:11:30 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_printf(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_putstr_printf(char *s, int *len)
{
	if (!s)
	{
		ft_putstr_printf("(null)", len);
		return ;
	}
	while (*s)
	{
		ft_putchar_printf(*s, len);
		s++;
	}
}
