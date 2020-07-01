/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:18:13 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:29:15 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

/*
** check keyword from .cub file
** texture keyword : NO, SO, WE, EA, S
*/

void	set_player_direction(t_cub *cub, int y, int x)
{
	if (cub->map[y][x] == 'N')
		cub->player_dir = 270.0;
	else if (cub->map[y][x] == 'S')
		cub->player_dir = 90.0;
	else if (cub->map[y][x] == 'W')
		cub->player_dir = 180.0;
	else
		cub->player_dir = 0.0;
	cub->player_x = x;
	cub->player_y = y;
}

int		set_player(t_cub *cub)
{
	int		x;
	int		y;
	int		chk;

	chk = 0;
	y = -1;
	while (++y < cub->map_h)
	{
		x = -1;
		while (++x < cub->map_w)
		{
			if (ft_strchr("NSWE", cub->map[y][x]))
			{
				set_player_direction(cub, y, x);
				chk++;
			}
		}
	}
	if (chk == 1)
		return (1);
	return (0);
}

int		check_sum(int check_sum)
{
	if (check_sum != 0b11111111)
		return (error("cub file error"));
	return (1);
}

int		parse_scene(char *filepath, t_cub *cub)
{
	int		fd;
	int		check;
	char	*line;

	check = 0b00000000;
	cub->line_n = 0;
	fd = open(filepath, O_RDONLY);
	if (fd <= 0)
		return (error("file open error"));
	while (get_next_line(fd, &line) > 0)
	{
		cub->line_n += 1;
		if (is_resolution(line) && !(check_resolution(line, cub, &check)))
			return (0);
		else if (is_texture(line) && !(check_texture(line, cub, &check)))
			return (0);
		else if (is_floor_ceiling(line) && !(check_color(line, cub, &check)))
			return (0);
		if (check == 0b11111111 && !(check_map(fd, cub, filepath)))
			return (0);
		free(line);
	}
	free(line);
	close(fd);
	return (check_sum(check));
}
