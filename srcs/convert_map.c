/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:22:48 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 20:10:33 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	convert_space(t_cub *cub, int r, int c)
{
	int		t;
	int		check;

	t = 1;
	check = 0;
	if (cub->map[r][c] == ' ')
	{
		while (c + t < cub->map_w && c - t >= 0)
		{
			if ((cub->map[r][c + t] != '1' && cub->map[r][c + t] != ' ') || \
				(cub->map[r][c - t] != '1' && cub->map[r][c - t] != ' '))
			{
				cub->map[r][c] = '0';
				check = 1;
				break ;
			}
			t++;
		}
		if (check == 0)
			cub->map[r][c] = '1';
	}
}

int		convert_map(t_cub *cub)
{
	int		r;
	int		c;

	r = -1;
	while (++r < cub->map_h)
	{
		c = -1;
		while (++c < cub->map_w)
		{
			if (cub->map[r][c] == ' ')
				cub->map[r][c] = '0';
		}
	}
	return (0);
}
