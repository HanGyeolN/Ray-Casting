#include "raycasting.h"
#include <stdio.h>

int		is_ray_inf(t_ray *ray)
{
	if (ray->rad >= 88 && ray->rad <= 92)
		return (1);
	else if (ray->rad >= 268 && ray->rad <= 272)
		return (-1);
	return(0);
}

int		is_hit(t_ray *ray, double x, double y, t_map *map)
{
	if (map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] == '1')
	{
		
		ray->hit_x = x;
		ray->hit_y = y;
		ray->dist = (ray->hit_x - ray->pos_x) * (ray->hit_x - ray->pos_x);
		ray->dist += (ray->hit_y - ray->pos_y) * (ray->hit_y - ray->pos_y);
		ray->dist = sqrt(ray->dist);
		// printf("val: %f", ray->dist);
		// if (map->map[(int)(y / map->block_h)][(int)((x - 1)/ map->block_w)] == '0' || 
		// 	map->map[(int)(y / map->block_h)][(int)((x + 1)/ map->block_w)] == '0')
		// 	ray->dist = sin((ray->rad * PI / 180.0) - (player.rad * PI / 180.0)) * ray->dist;
		// else
		ray->dist = cos((ray->rad * PI / 180.0) - (player.rad * PI / 180.0)) * ray->dist;
		// printf(", cos: %f -> %f\n", cos((ray->rad * PI / 180.0) - (player.rad * PI / 180.0)), ray->dist);
		// printf("angle: %f, %f \n", ray->rad, player.rad);
		return (1);
	}
	return (0);
}

int		line_put(t_window *w, t_ray *ray, t_map *map)
{
	double		ty;
	double		dx;
	int			x;
	int			y;

	x = ray->pos_x;
	y = ray->pos_y;
	dx = (ray->rad >= 90 && ray->rad <= 270) ? -1 : 1;
	if (ray->dydx > 1.0 && ray->rad <= 90)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map))
					return (0);
				img_data1[(int)y * (int)window->width + (int)x] = ray->color;
				y++;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 180)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map))
					return (0);
				img_data1[(int)y * (int)window->width + (int)x] = ray->color;
				y++;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx > 1.0 && ray->rad <= 270)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map))
					return (0);
				img_data1[(int)y * (int)window->width + (int)x] = ray->color;
				y--;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 360)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map))
					return (0);
				img_data1[(int)y * (int)window->width + (int)x] = ray->color;
				y--;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else
	{
		while (!is_hit(ray, x, y, map))
		{
			img_data1[(int)y * (int)window->width + (int)x] = ray->color;
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	return (0);
}

void	render_wall(t_window *window, t_ray *ray, int i, char mode)
{
	int		j;
	int		y;
	int		ray_w;
	double	wall_h;
	double	color;
	double	color_q;
	double	max_len;
	int		size;
	void	*img_ptr;
	
	j = -1;
	ray_w = (int)(window->gw / N_RAY);
	max_len = sqrt(pow(window->width, 2) + pow(window->height, 2));
	color_q = 0x0000FF / (max_len / 1.5);
	color = 0xFFFFFF;
	color -= (int)(color_q * ray->dist);
	color -= 16 * 16 * (int)(color_q * ray->dist);
	color -= 16 * 16 * 16 * 16 * (int)(color_q * ray->dist);
	if (mode == 'd')
		color = 0x000000;
	wall_h = (window->height / (ray->dist / 7));
	while (++j < ray_w)
	{
		y = (int)round((window->height / 2.0) - (wall_h / 2.0));
		while (y < (int)round((window->height / 2.0) + (wall_h / 2.0)))
		{
			img_data2[y * (int)window->width + ((ray_w * i) + j)] = color;
			y++;
		}
	}
}

void	render_ray(t_window *window, t_ray *ray, t_map *map)
{
	double		dx;
	double		x;
	double		y;

	x = ray->pos_x;
	y = ray->pos_y;
	if (is_ray_inf(ray))
	{
		while (!is_hit(ray, x, y, map))
		{
			img_data1[(int)y * (int)window->width + (int)x] = ray->color;
			y += ray->dydx;
		}
	}
	else 
		line_put(window, ray, map);
}

void	render_block(t_window *window, t_map *map, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->block_w)
	{
		j = 0;
		while (j < map->block_h)
		{
			//printf("%d\n", (map->block_h * y + j));
			//printf("%d\n", (int)(window->width));
			//printf("%d\n", (map->block_w * x + i));
			img_data1[(map->block_h * y + j) * (int)window->width + (map->block_w * x + i)] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

int		render_map(t_window *window, t_map *map)
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
				render_block(window, map, x, y);
		}
	}
	return (0);
}

void	render(void)
{
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img_ptr1, 0, 0);
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, img_ptr2, (int)window->width, 0);
}