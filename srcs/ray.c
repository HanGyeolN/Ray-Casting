#include "raycasting.h"

int		is_ray_inf(t_ray *ray)
{
	if (ray->rad >= 89.9 && ray->rad <= 90.1)
		return (1);
	else if (ray->rad >= 269.9 && ray->rad <= 270.1)
		return (-1);
	return(0);
}

int		is_hit(t_ray *ray, double x, double y, t_map *map, t_scene *scene)
{
	if (map->map[(int)(y / map->block_h)][(int)(x / map->block_w)] == '1')
	{
		ray->hit_x = x;
		ray->hit_y = y;
		if ((int)ray->hit_x % map->block_h == map->block_h - 1)
			ray->side = 0;
		else if ((int)ray->hit_y % map->block_w == map->block_w - 1)
			ray->side = 0;
		else if ((int)ray->hit_x % map->block_h == 0)
			ray->side = 0;
		else if ((int)ray->hit_y % map->block_w == 0)
			ray->side = 0;
		ray->dist = (ray->hit_x - ray->pos_x) * (ray->hit_x - ray->pos_x);
		ray->dist += (ray->hit_y - ray->pos_y) * (ray->hit_y - ray->pos_y);
		ray->dist = sqrt(ray->dist);
		ray->dist = cos((ray->rad * PI / 180.0) - ((scene->player).rad * PI / 180.0)) * ray->dist;
		return (1);
	}
	return (0);
}

int		ray_casting(t_ray *ray, t_map *map, t_scene *scene)
{
	double		ty;
	double		dx;
	int			x;
	int			y;

	x = ray->pos_x;
	y = ray->pos_y;
	if (is_ray_inf(ray))
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			(map->data)[y * MAP_VIEW_W + x] = ray->color;
			y += ray->dydx;
		}
		return (0);
	}
	dx = (ray->rad >= 90 && ray->rad <= 270) ? -1 : 1;
	if (ray->dydx > 1.0 && ray->rad <= 90)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				(map->data)[y * MAP_VIEW_W + x] = ray->color;
				y++;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 180)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				(map->data)[y * MAP_VIEW_W + x] = ray->color;
				y++;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx > 1.0 && ray->rad <= 270)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				(map->data)[y * MAP_VIEW_W + x] = ray->color;
				y--;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 360)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				(map->data)[y * MAP_VIEW_W + x] = ray->color;
				y--;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			(map->data)[y * MAP_VIEW_W + x] = ray->color;
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	return (0);
}