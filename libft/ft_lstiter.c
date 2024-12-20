/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:45:36 by sklaps            #+#    #+#             */
/*   Updated: 2024/04/17 15:50:13 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int	i;
	int	j;

	i = 0;
	j = ft_lstsize(lst);
	while (i++ < j)
	{
		f(lst->content);
		lst = lst->next;
	}
}
