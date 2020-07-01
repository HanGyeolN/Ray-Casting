/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 13:45:40 by hna               #+#    #+#             */
/*   Updated: 2020/03/03 16:24:39 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static t_buffer	buf;

	if (BUFFER_SIZE < 1 || line == 0)
		return (-1);
	if (init_set(fd, line, &buf) == -1 || read_if_empty(&buf) == -1)
		return (-1);
	while (buf.read_n != 0)
	{
		*line = ft_strjoin_eol(*line, &(buf.buf[buf.cur_idx]));
		while (buf.buf[buf.cur_idx] != '\n' && buf.buf[buf.cur_idx] != '\0')
			buf.cur_idx += 1;
		if (buf.cur_idx == BUFFER_SIZE || buf.buf[buf.cur_idx] == '\0')
		{
			init_read(&buf);
			if (buf.buf[buf.cur_idx] == '\0')
				return (0);
		}
		else
		{
			buf.cur_idx++;
			return (1);
		}
	}
	return (0);
}
