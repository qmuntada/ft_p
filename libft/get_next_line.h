/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 15:17:34 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/15 16:58:53 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_fd
{
	int				fd;
	char			*original_ptr;
	char			*current_ptr;
	struct s_fd		**begin;
	struct s_fd		*next;
	struct s_fd		*prev;
}					t_fd;

int					get_next_line(int const fd, char **line);

#endif
