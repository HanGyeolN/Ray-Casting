/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:04:32 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 20:29:41 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

char	**make_base_and_paste_map(t_cub *cub)
{
	int		i;
	char	**base;

	i = 0;
	if (!(base = malloc(sizeof(char *) * (cub->map_h + 3))))
		return (0);
	base[cub->map_h + 2] = 0;
	while (i < cub->map_h + 2)
	{
		if (!(base[i] = malloc(sizeof(char) * (cub->map_w + 3))))
			return (0);
		ft_memset(base[i], 's', cub->map_w + 2);
		base[i][cub->map_w + 2] = 0;
		i++;
	}
	i = 0;
	while (i < cub->map_h)
	{
		ft_strncpy(base[i + 1] + 1, cub->map[i], ft_strlen(cub->map[i]));
		i++;
	}
	return (base);
}

void	padding_s(t_cub *cub, char **base)
{
	int		r;
	int		c;

	r = 0;
	while (++r < cub->map_h + 1)
	{
		c = 0;
		while (++c < cub->map_w + 1)
		{
			if (base[r][c] == ' ' && (base[r - 1][c] == 's' || base[r + 1][c] \
				== 's' || base[r][c - 1] == 's' || base[r][c + 1] == 's'))
				base[r][c] = 's';
		}
	}
	r = cub->map_h + 1;
	while (--r > 0)
	{
		c = cub->map_w + 1;
		while (--c > 0)
		{
			if (base[r][c] == ' ' && (base[r - 1][c] == 's' || base[r + 1][c] \
				== 's' || base[r][c - 1] == 's' || base[r][c + 1] == 's'))
				base[r][c] = 's';
		}
	}
}

int		is_wall_or_s(char c)
{
	if (c == '1' || c == 's')
		return (1);
	return (0);
}

int		check_edge(t_cub *cub, char **base)
{
	int		r;
	int		c;

	r = -1;
	while (++r < cub->map_h + 2)
	{
		c = -1;
		while (++c < cub->map_w + 2)
		{
			if (base[r][c] == 's')
			{
				if (r - 1 > 0 && !(is_wall_or_s(base[r - 1][c])))
					return (0);
				if (r + 1 < cub->map_h + 2 && !(is_wall_or_s(base[r + 1][c])))
					return (0);
				if (c - 1 > 0 && !(is_wall_or_s(base[r][c - 1])))
					return (0);
				if (c + 1 < cub->map_w + 2 && !(is_wall_or_s(base[r][c + 1])))
					return (0);
			}
		}
	}
	return (1);
}

int		is_closed(t_cub *cub)
{
	int		i;
	int		closed;
	char	**base;

	base = make_base_and_paste_map(cub);
	padding_s(cub, base);
	closed = check_edge(cub, base);
	i = 0;
	while (i < cub->map_h + 2)
	{
		free(base[i]);
		i++;
	}
	free(base);
	if (closed)
		return (1);
	else
		return (0);
}
