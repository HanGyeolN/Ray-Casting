/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:20:28 by hna               #+#    #+#             */
/*   Updated: 2020/03/30 16:37:48 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlcat_eol(char *dst, const char *src, size_t dst_size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	i = 0;
	src_len = (size_t)ft_strlen((char *)src);
	dst_len = (size_t)ft_strlen((char *)dst);
	if (dst_size < dst_len)
		return (dst_size + src_len);
	while (dst_size > dst_len + i + 1 && i < src_len && src[i] != '\n')
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + src_len);
}

char			*ft_strjoin_eol(char *s1, char *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = (size_t)ft_strlen((char *)s1);
	s2_len = (size_t)ft_strlen((char *)s2);
	if (!(ret = malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcat_eol(ret, s2, s1_len + s2_len + 1);
	free(s1);
	return (ret);
}
