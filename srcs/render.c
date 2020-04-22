#include "raycasting.h"
#include <stdio.h>

void	convert_3d(t_window *window, t_ray *ray, int i, char mode, t_scene *scene)
{
	int		j;
	int		y;
	int		ray_w;
	double	wall_h;
	double	color;
	double	color_q;
	double	max_len;
	int		tar_x;
	int		tar_y;
	
	j = -1;
	ray_w = (int)(WIDTH / N_RAY);
	max_len = sqrt(pow(window->width, 2) + pow(window->height, 2));
	color_q = 0x0000FF / (max_len / 1.5);
	color = 0xFFFFFF;
	color -= (int)(color_q * ray->dist);
	color -= 16 * 16 * (int)(color_q * ray->dist);
	color -= 16 * 16 * 16 * 16 * (int)(color_q * ray->dist);
	if (mode == 'd')
		color = 0x000000;
	wall_h = (window->height / (ray->dist / 10));
	if (mode == 'd')
	{
		while (++j < ray_w)
		{
			y = (int)round((window->height / 2.0) - (wall_h / 2.0));
			while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
			{
				window->img_data[y * (int)window->width + (j + (ray_w * i))] = 0x000000;
				y++;
			}
		}
		return ;
	}
	if (ray->side == 0)
	{
		y = (int)round((window->height / 2.0) - (wall_h / 2.0));
		tar_x = (int)((TEXTURE_SIZE / (scene->map).block_w) * (((int)ray->hit_y) % (scene->map).block_w));
		while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
		{
			tar_y = (int)((TEXTURE_SIZE / wall_h) * (y - (int)round((window->height / 2.0) - (wall_h / 2.0))));
			window->img_data[y * (int)window->width + (ray_w * i)] = \
				(scene->texture).n_data[tar_y][tar_x];
			y++;
		}
	}
	else if (ray->side == 1)
	{
		y = (int)round((window->height / 2.0) - (wall_h / 2.0));
		tar_x = (int)((TEXTURE_SIZE / (scene->map).block_w) * (((int)ray->hit_y) % (scene->map).block_w));
		while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
		{
			tar_y = (int)((TEXTURE_SIZE / wall_h) * (y - (int)round((window->height / 2.0) - (wall_h / 2.0))));
			window->img_data[y * (int)window->width + (ray_w * i)] = \
				(scene->texture).s_data[tar_y][tar_x];
			y++;
		}
	}
	else if (ray->side == 2)
	{
		y = (int)round((window->height / 2.0) - (wall_h / 2.0));
		tar_x = (int)((TEXTURE_SIZE / (scene->map).block_w) * (((int)ray->hit_x) % (scene->map).block_w));
		while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
		{
			tar_y = (int)((TEXTURE_SIZE / wall_h) * (y - (int)round((window->height / 2.0) - (wall_h / 2.0))));
			window->img_data[y * (int)window->width + (ray_w * i)] = \
				(scene->texture).e_data[tar_y][tar_x];
			y++;
		}
	}
	else if (ray->side == 3)
	{
		y = (int)round((window->height / 2.0) - (wall_h / 2.0));
		tar_x = (int)((TEXTURE_SIZE / (scene->map).block_w) * (((int)ray->hit_x) % (scene->map).block_w));
		while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
		{
			tar_y = (int)((TEXTURE_SIZE / wall_h) * (y - (int)round((window->height / 2.0) - (wall_h / 2.0))));
			window->img_data[y * (int)window->width + (ray_w * i)] = \
				(scene->texture).w_data[tar_y][tar_x];
			y++;
		}
	}
}

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
			(map->data)[(map->block_h * y + j) * (int)map->width_r + (map->block_w * x + i)] = 0xFFFFFF;
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
//	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img_ptr1, 0, HEIGHT - MAP_VIEW_H);
}