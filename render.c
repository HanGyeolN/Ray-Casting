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
		ray->dist = pow(ray->hit_x - ray->pos_x, 2);
		ray->dist += pow(ray->hit_y - ray->pos_y, 2);
		ray->dist = sqrt(ray->dist);
		return (1);
	}
	return (0);
}

int		line_put(t_window *w, t_ray *ray, t_map *map)
{
	double		ty;
	double		dx;
	double		x;
	double		y;

	x = ray->pos_x;
	y = ray->pos_y;
	dx = (ray->rad >= 90 && ray->rad <= 270) ? -1 : 1;
	if (ray->dydx > 1.0 && ray->rad <= 90)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (++y < ty && !is_hit(ray, x, y, map))
				mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 180)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (++y < ty && !is_hit(ray, x, y, map))
				mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
	else if (ray->dydx > 1.0 && ray->rad <= 270)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (--y > ty && !is_hit(ray, x, y, map))
				mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 360)
	{
		while (!is_hit(ray, x, y, map))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (--y > ty && !is_hit(ray, x, y, map))
				mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
	else
	{
		while (!is_hit(ray, x, y, map))
		{
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
	return (0);
}

void	render_wall(t_window *window, t_ray *ray, int i)
{
	int		j;
	int		y;
	int		ray_w;
	double	color;
	double	color_q;
	double	max_len;
	
	j = -1;
	ray_w = (int)(window->gw / N_RAY);
	max_len = sqrt(pow(window->width, 2) + pow(window->height, 2));
	color_q = 0x0000FF / max_len;
	color = 0xFFFFFF;
	color -= (int)(color_q * ray->dist);
	color -= 16 * 16 * (int)(color_q * ray->dist);
	color -= 16 * 16 * 16 * 16 * (int)(color_q * ray->dist);
	while (++j < ray_w)
	{
		y = -1;
		while (++y < window->height)
		{
			mlx_pixel_put(window->mlx_ptr, 
						window->win_ptr,
						(ray_w * i) + j + window->width, 
						y,
						color);
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
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, (int)x, (int)y, ray->color);
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

	i = -1;
	while (++i < map->block_w)
	{
		j = -1;
		while (++j < map->block_h)
		{
			mlx_pixel_put(window->mlx_ptr, 
						  window->win_ptr, 
						  x * map->block_w + i,
						  y * map->block_h + j,
						  map->color);
		}
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