/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:20:59 by sklaps            #+#    #+#             */
/*   Updated: 2024/04/15 10:34:07 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_tmp;
	char	*little_tmp;
	int		i;

	if (!ft_strlen(little))
		return ((char *)big);
	if (!ft_strlen(big) || len < ft_strlen(little))
		return (NULL);
	i = len - ft_strlen(little) + 1;
	while (i-- && *big)
	{
		big_tmp = (char *)big;
		little_tmp = (char *)little;
		while (*little_tmp && *little_tmp == *big_tmp)
		{
			++little_tmp;
			++big_tmp;
		}
		if (!*little_tmp)
			return ((char *)big);
		++big;
	}
	return (NULL);
}
