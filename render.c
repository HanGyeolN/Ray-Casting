#include "raycasting.h"

int		is_ray_inf(t_ray *ray)
{
	if (ray->rad >= 89.5 && ray->rad <= 90.5)
		return (1);
	else if (ray->rad >= 269.5 && ray->rad <= 270.5)
		return (-1);
	return(0);
}

int		line_put(t_window *w, t_ray *ray, double x, double y)
{
	double		ty;

	if (is_ray_inf(ray))
	{
		while (y >= 0 && y < w->height)
		{
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, 0xFFFFFF);
			y += ray->dydx;
		}
		return (1);
	}
	if (ray->dydx > 1.0 || ray->dydx < -1.0)
	{
		if (ray->dydx > 0)
			ty = ray->dydx * ((x - 1.0) - ray->pos_x) + ray->pos_y;
		else
			ty = ray->dydx * ((x + 1.0) - ray->pos_x) + ray->pos_y;
		while (++ty < y)
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)ty, 0xFFFFFF);
	}
	else
		mlx_pixel_put(w->mlx_ptr, w->win_ptr, (int)x, (int)y, 0xFFFFFF);
	return (0);
}

void	render_ray(t_window *window, t_ray *ray)
{
	double		x;
	double		y;
	
	x = (double)ray->pos_x;
	y = (double)ray->pos_y;
	while ((x >= 0 && x < window->width) && (y >= 0 && y < window->height))
	{
		if (!(is_ray_inf(ray)))
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		if (line_put(window, ray ,x, y) == 1)
			break;
		if (ray->rad >= 90 && ray->rad <= 270)
			x--;
		else
			x++;
	}
}

int		render_map(t_window *window, t_map *map)
{
	int		x;
	int		y;

	x = -1;
	while (++x < window->width)
	{
		y = -1;
		while (++y < window->height)
		{
			if (map->map[(int)(y / (window->height / map->height))][(int)(x / (window->width / map->width))] == '1')
				mlx_pixel_put(window->mlx_ptr, window->win_ptr, x, y, 0xFFFFFF);
		}
	}
	return (0);
}