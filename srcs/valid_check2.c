/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:19:37 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 20:03:53 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		is_valid_character(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == '\n')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '2')
		return (1);
	return (0);
}

int		is_valid_characters(t_cub *cub)
{
	int		r;
	int		c;

	c = -1;
	while (++c < cub->map_w)
	{
		r = -1;
		while (++r < cub->map_h)
		{
			if (!(is_valid_character(cub->map[r][c])))
			{
				error("map error | not a valid character");
				ft_printf("map (%d, %d) : %c", r, c, cub->map[r][c]);
				return (0);
			}
		}
	}
	return (1);
}

int		is_valid_map(t_cub *cub)
{
	if (!(is_closed(cub)))
		return (error("not closed"));
	if (!(is_valid_characters(cub)))
		return (0);
	return (1);
}

int		is_valid_color(char **colors)
{
	int		idx;
	int		i;

	idx = 0;
	i = -1;
	while (idx < 3)
	{
		while (++i < ft_strlen(colors[idx]))
			if (is_numeric(colors[idx][i]) == 0)
				return (0);
		if (ft_atoi(colors[idx]) < 0 || ft_atoi(colors[idx]) > 255)
			return (0);
		idx++;
	}
	return (1);
}
