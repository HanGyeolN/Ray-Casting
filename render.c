#include "raycasting.h"

int		is_ray_inf(t_ray *ray)
{
	if (ray->rad >= 89.5 && ray->rad <= 90.5)
		return (1);
	else if (ray->rad >= 269.5 && ray->rad <= 270.5)
		return (-1);
	return(0);
}

int		line_put(t_window *w, t_ray *ray, double x, double y, t_map *map)
{
	double		ty;

	if (is_ray_inf(ray))
	{
		while (map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
		{
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
			y += ray->dydx;
		}
		return (1);
	}
	if (ray->dydx > 1.0 && ray->rad <= 90)
	{
		ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
		while (++y < ty && map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
	}
	else if (ray->dydx < -1.0 && ray->rad <= 180)
	{
		ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
		while (++y < ty && map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
	}
	else if (ray->dydx > 1.0 && ray->rad <= 270)
	{
		ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
		while (--y > ty && map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
	}
	else if (ray->dydx < -1.0 && ray->rad <= 360)
	{
		ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
		while (--y > ty && map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
	}
	else
		mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, ray->color);
	return (0);
}

void	render_ray(t_window *window, t_ray *ray, t_map *map)
{
	double		dx;
	double		x;
	double		y;

	x = ray->pos_x;
	y = ray->pos_y;
	dx = (ray->rad >= 90 && ray->rad <= 270) ? -1 : 1;
	if (is_ray_inf(ray))
		line_put(window, ray, x, y, map);
	else
	{
		while (map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] != '1')
		{
			line_put(window, ray, x, y, map);
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			x += dx;
		}
	}
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