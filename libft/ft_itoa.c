/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:00:46 by sklaps            #+#    #+#             */
/*   Updated: 2024/04/16 16:07:27 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(int n)
{
	int	len;
	int	sign;

	len = 0;
	sign = 0;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
	{
		n /= 10;
		len++;
	}
	if (n < 0)
	{
		sign = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len + sign);
}

static void	fill(char *ret, int n, int len, int sign)
{
	len--;
	while (len >= sign)
	{
		ret[len] = (n % 10) + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		len;
	int		sign;

	sign = 0;
	len = numlen(n);
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[len] = '\0';
	if (n == INT_MIN)
	{
		len--;
		ret[len] = '8';
		n /= 10;
	}
	if (n < 0)
	{
		n = -n;
		ret[0] = '-';
		sign = 1;
	}
	fill(ret, n, len, sign);
	return (ret);
}
