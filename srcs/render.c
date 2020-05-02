#include "raycasting.h"
#include <stdio.h>

void	put_block_to_img(t_map *map, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->block_w)
	{
		j = 0;
		while (j < map->block_h)
		{
			(map->data)[(map->block_h * y + j) * (int)map->width + (map->block_w * x + i)] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

int		put_map_to_img(t_map *map)
{
	int		x;
	int		y;

	x = -1;
	while (++x < map->width)
	{
		y = -1;
		while (++y < map->height)
		{
			if (map->map[y][x] == '1')
				put_block_to_img(map, x, y);
		}
	}
	return (0);
}

void	render(t_scene *scene)
{
	mlx_put_image_to_window((scene->window).mlx_ptr, (scene->window).win_ptr, (scene->window).img_ptr, 0, 0);
	//mlx_put_image_to_window((scene->window).mlx_ptr, (scene->window).win_ptr, (scene->map).image, 0, (scene->window).height - (scene->map).height_r);
}