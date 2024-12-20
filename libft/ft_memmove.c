/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:49:36 by sklaps            #+#    #+#             */
/*   Updated: 2024/04/11 20:08:02 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*ret;

	if (!dest && !src)
		return (0);
	ret = dest;
	if (src < dest)
	{
		src += n;
		dest += n;
		while (n--)
			*(char *)--dest = *(char *)--src;
	}
	else
		while (n--)
			*(char *)dest++ = *(char *)src++;
	return (ret);
}
