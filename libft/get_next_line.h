/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaps <sklaps@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:13:13 by sklaps            #+#    #+#             */
/*   Updated: 2024/06/03 15:01:32 by sklaps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
}	t_lst;

int		len_to_newline(t_lst *list);
t_lst	*gnl_lstlast(t_lst *lst);
void	gnl_lstclear(t_lst **list, t_lst *new_node, char *buf);
void	polish_list(t_lst **list);
char	*get_next_line(int fd);
char	*get_line(t_lst *list);
void	create_list(t_lst **list, int fd);
void	append(t_lst **lst, char *buf);
int		found_newline(t_lst *list);
void	copy_str(t_lst *list, char *ret);

#endif
