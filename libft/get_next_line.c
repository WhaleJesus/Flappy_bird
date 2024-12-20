/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:27:19 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:21:19 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_lst *list)
{
	int	i;

	if (list == NULL)
		return (0);
	list = gnl_lstlast(list);
	i = 0;
	while (list->content[i] && i < BUFFER_SIZE)
		if (list->content[i++] == '\n')
			return (1);
	return (0);
}

void	append(t_lst **list, char *buf)
{
	t_lst	*new_node;
	t_lst	*last_node;

	last_node = gnl_lstlast(*list);
	new_node = malloc(sizeof(t_lst));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	create_list(t_lst **list, int fd)
{
	char	*buf;
	int		char_read;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_line(t_lst *list)
{
	int		len;
	char	*ret;

	if (list == NULL)
		return (NULL);
	len = len_to_newline(list);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	copy_str(list, ret);
	return (ret);
}

char	*get_next_line(int fd)
{
	static t_lst	*list;
	char			*next_line;

	if (!list)
		list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (NULL == list)
		return (NULL);
	next_line = get_line(list);
	if (NULL == next_line)
		return (NULL);
	polish_list(&list);
	return (next_line);
}
