/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:48:00 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:15:06 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define HEX_LOWCASE "0123456789abcdef"
# define HEX_UPCASE "0123456789ABCDEF"

int		ft_printf(const char *str, ...);
void	ft_checktype_printf(char c, va_list *args, int *len);
void	ft_putchar_printf(char c, int *len);
void	ft_putstr_printf(char *s, int *len);
void	ft_putnbr_printf(int n, int *len);
void	ft_puthex_printf(unsigned int number, int flag, int *len);
void	ft_putptr_printf(unsigned long int ptr, int *len);
void	ft_putnbr_unsigned_printf(unsigned int n, int *len);

#endif
