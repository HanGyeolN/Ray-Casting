/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 18:14:56 by hna               #+#    #+#             */
/*   Updated: 2020/03/03 18:15:25 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*ret;

	src_len = ft_strlen((char *)src);
	ret = malloc(sizeof(char) * (src_len + 1));
	ft_strlcpy(ret, src, (size_t)(src_len + 1));
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;

	i = 0;
	while (i < dst_size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dst_size != 0)
		dst[dst_size - 1] = '\0';
	return (i);
}

size_t	ft_strlcat_eol(char *dst, const char *src, size_t dst_size)
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

char	*ft_strjoin_eol(char *s1, char *s2)
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
