/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:14:37 by hna               #+#    #+#             */
/*   Updated: 2020/03/03 18:14:41 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		read_if_empty(t_buffer *buf)
{
	if (!(buf->buf[0]))
		buf->read_n = read(buf->fd, buf->buf, BUFFER_SIZE);
	if (buf->read_n < 0)
		return (-1);
	return (0);
}

void	init_read(t_buffer *buf)
{
	int		i;

	i = BUFFER_SIZE + 1;
	while (--i >= 0)
		buf->buf[i] = 0;
	buf->read_n = read(buf->fd, buf->buf, BUFFER_SIZE);
	buf->cur_idx = 0;
}

int		init_set(int fd, char **line, t_buffer *buf)
{
	buf->fd = fd;
	if (fd < 0 || !(*line = malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static t_buffer	buf[1024];

	if (BUFFER_SIZE < 1 || line == 0)
		return (-1);
	if (init_set(fd, line, &buf[fd]) == -1 || read_if_empty(&buf[fd]) == -1)
		return (-1);
	while (buf[fd].read_n != 0)
	{
		*line = ft_strjoin_eol(*line, &(buf[fd].buf[buf[fd].cur_idx]));
		while (buf[fd].buf[buf[fd].cur_idx] != '\n' && buf[fd].buf[buf[fd].cur_idx] != '\0')
			buf[fd].cur_idx += 1;
		if (buf[fd].cur_idx == BUFFER_SIZE || buf[fd].buf[buf[fd].cur_idx] == '\0')
		{
			init_read(&buf[fd]);
			if (buf[fd].buf[buf[fd].cur_idx] == '\0')
				return (0);
		}
		else
		{
			buf[fd].cur_idx++;
			return (1);
		}
	}
	return (0);
}
