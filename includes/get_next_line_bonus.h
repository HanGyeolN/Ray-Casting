/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:15:58 by hna               #+#    #+#             */
/*   Updated: 2020/03/30 16:08:58 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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

int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t	ft_strlcat_eol(char *dst, const char *src, size_t dst_size);
char	*ft_strjoin_eol(char *s1, char *s2);

#endif
