/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:43:38 by hna               #+#    #+#             */
/*   Updated: 2020/06/29 19:02:07 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 100

typedef struct	s_buffer
{
	int		fd;
	int		cur_idx;
	int		read_n;
	char	buf[BUFFER_SIZE + 1];
}				t_buffer;

int				get_next_line(int fd, char **line);
size_t			ft_strlcat_eol(char *dst, const char *src, size_t dst_size);
char			*ft_strjoin_eol(char *s1, char *s2);

#endif
