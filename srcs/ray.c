#include "raycasting.h"

int		is_ray_inf(t_ray *ray)
{
	if (ray->rad >= 89.99 && ray->rad <= 90.01)
		return (1);
	else if (ray->rad >= 269.99 && ray->rad <= 270.01)
		return (-1);
	return(0);
}

int		is_hit(t_ray *ray, double x, double y, t_map *map, t_scene *scene)
{
	int		i;
	int		j;

	i = (int)x;
	j = (int)y;
	if (map->map_r[j][i] == '1')
	{
		ray->hit_x = x;
		ray->hit_y = y;
		if (map->map_r[j - 1][i] == '0' && ray->rad >= 0.0 && ray->rad <= 180.0)
		{
			ray->hit_x = x;
			ray->hit_y = (float)j;
			ray->side = 0;
		}
		else if (map->map_r[j + 1][i] == '0' && ray->rad >= 180.0 && ray->rad <= 360.0)
		{
			ray->hit_x = x;
			ray->hit_y = (float)j;
			ray->side = 2;
		}
		else if (map->map_r[j][i + 1] == '0' && ray->rad >= 90.0 && ray->rad <= 270.0)
		{
			ray->hit_x = (float)i;
			ray->hit_y = y;
			ray->side = 1;
		}
		else if (map->map_r[j][i - 1] == '0' && !(ray->rad >= 90.0 && ray->rad <= 270.0))
		{
			ray->hit_x = (float)i;
			ray->hit_y = y;
			ray->side = 3;
		}
		else
			ray->side = 4;
		if (ray->side == 1 || ray->side == 3)
		{
			ray->dist = (ray->hit_x - ray->pos_x) * (ray->hit_x - ray->pos_x);
			ray->dist += (ray->hit_y - ray->pos_y) * (ray->hit_y - ray->pos_y);
			ray->dist = sqrt(ray->dist);
			ray->dist = cos((ray->rad - (scene->player).rad) * PI / 180.0) * ray->dist;
		}
		else
		{
			ray->dist = (ray->hit_x - ray->pos_x) * (ray->hit_x - ray->pos_x);
			ray->dist += (ray->hit_y - ray->pos_y) * (ray->hit_y - ray->pos_y);
			ray->dist = sqrt(ray->dist);
			if ((scene->player).rad > ray->rad)
				ray->dist = cos(((scene->player).rad - ray->rad) * PI / 180.0) * ray->dist;
			else
				ray->dist = cos((ray->rad - (scene->player).rad) * PI / 180.0) * ray->dist;
		}
		return (1);
	}
	return (0);
}

double	distance(double s_x, double s_y, double e_x, double e_y)
{
	//return (sqrt(pow(s_x - e_x, 2.0) + pow(s_y - e_y, 2.0)));
	return (sqrt((s_x - e_x) * (s_x - e_x) + (s_y - e_y) * (s_y - e_y)));
}

int		ray_casting(t_ray *ray, t_map *map, t_scene *scene)
{
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	x;
	double	y;
	int		dx;
	int		dy;
	int		hit;
	int		side;
	int		pos;

	if (!scene)
		return (0);
	hit = 0;
	map_x = (int)ray->pos_x;
	map_y = (int)ray->pos_y;
	// if (is_ray_inf(ray))
	// {
	// 	// while (map->map_r[map_y][map_x] != '1')
	// 	// {
	// 	// 	pos = (int)(map_y * map->width_r + map_x);
	// 	// 	(map->data)[pos] = ray->color;
	// 	// 	map_y += (int)ray->dydx;
	// 	// }
	// 	side_dist_x = 9999999.0;
	// 	side_dist_y = 0.000001;
	// 	dx = 1;
	// 	dy = (ray->rad > 80.0 && ray->rad < 100.0) ? 1 : -1;
	// 	delta_dist_y = distance(0.0, 0.0, );
	// 	delta_dist_x = distance(0.0, 0.0, (1.0 / ray->dydx), 1.0);
	// 	while (hit == 0)
	// 	{
	// 		pos = (map_y * (int)map->width_r + map_x);
	// 		(map->data)[pos] = ray->color;
	// 		if (side_dist_x < side_dist_y)
	// 		{
	// 			side_dist_x += delta_dist_x;
	// 			map_x += dx;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			side_dist_y += delta_dist_y;
	// 			map_y += dy;
	// 			side = 1;
	// 		}
	// 		if (map->map_r[map_y][map_x] == '1')
	// 		{
	// 			hit = 1;
	// 			ray->hit_x = (double)map_x;
	// 			ray->hit_y = (double)map_y;
	// 			ray->dist = (side == 1) ? side_dist_y : side_dist_x;
	// 			if (map->map_r[map_y - 1][map_x] == '0' && ray->rad >= 0.0 && ray->rad <= 180.0)
	// 			{
	// 				ray->side = 0;
	// 			}
	// 			else if (map->map_r[map_y + 1][map_x] == '0' && ray->rad >= 180.0 && ray->rad <= 360.0)
	// 			{
	// 				ray->side = 2;
	// 			}
	// 			else if (map->map_r[map_y][map_x + 1] == '0' && ray->rad >= 90.0 && ray->rad <= 270.0)
	// 			{
	// 				ray->side = 1;
	// 			}
	// 			else if (map->map_r[map_y][map_x - 1] == '0' && !(ray->rad >= 90.0 && ray->rad <= 270.0))
	// 			{
	// 				ray->side = 3;
	// 			}
	// 			else
	// 				ray->side = 4;
	// 			if (ray->side == 1 || ray->side == 3)
	// 				ray->dist = cos((ray->rad - (scene->player).rad) * PI / 180.0) * ray->dist;
	// 			else
	// 			{
	// 				if ((scene->player).rad > ray->rad)
	// 					ray->dist = cos(((scene->player).rad - ray->rad) * PI / 180.0) * ray->dist;
	// 				else
	// 					ray->dist = cos((ray->rad - (scene->player).rad) * PI / 180.0) * ray->dist;
	// 			}
	// 		}
	// 	}
	// 	return (1);
	// }
	if (ray->rad >= 0.0 && ray->rad <= 90.0)
	{
		x = ceil(ray->pos_x);
		y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		side_dist_x = distance(ray->pos_x, ray->pos_y, x, y);
		y = ceil(ray->pos_y);
		x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		side_dist_y = distance(ray->pos_x, ray->pos_y, x, y);
		dx = 1;
		dy = 1;
	}
	else if (ray->rad > 90.0 && ray->rad <= 180.0)
	{
		x = floor(ray->pos_x);
		y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		side_dist_x = distance(ray->pos_x, ray->pos_y, x, y);
		y = ceil(ray->pos_y);
		x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		side_dist_y = distance(ray->pos_x, ray->pos_y, x, y);
		dx = -1;
		dy = 1;
	}
	else if (ray->rad > 180.0 && ray->rad <= 270.0)
	{
		x = floor(ray->pos_x);
		y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		side_dist_x = distance(ray->pos_x, ray->pos_y, x, y);
		y = floor(ray->pos_y);
		x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		side_dist_y = distance(ray->pos_x, ray->pos_y, x, y);
		dx = -1;
		dy = -1;
	}
	else
	{
		x = ceil(ray->pos_x);
		y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		side_dist_x = distance(ray->pos_x, ray->pos_y, x, y);
		y = floor(ray->pos_y);
		x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		side_dist_y = distance(ray->pos_x, ray->pos_y, x, y);
		dx = 1;
		dy = -1;
	}
	delta_dist_x = distance(0.0, 0.0, 1.0, ray->dydx);
	delta_dist_y = distance(0.0, 0.0, (1.0 / ray->dydx), 1.0);
	double tx, ty;
	tx = side_dist_x;
	ty = side_dist_y;
	while (hit == 0)
	{
		pos = (map_y * (int)map->width_r + map_x);
		(map->data)[pos] = ray->color;
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += dx;
			side = 1;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += dy;
			side = 0;
		}
		if (map->map_r[map_y][map_x] == '1')
		{
			hit = 1;
			ray->hit_x = (double)map_x;
			ray->hit_y = (double)map_y;
			ray->dist = (side == 1) ? side_dist_x : side_dist_y;
			if (map->map_r[map_y - 1][map_x] == '0' && side == 0)
			{
				ray->side = 0;
			}
			else if (map->map_r[map_y + 1][map_x] == '0' && side == 0)
			{
				ray->side = 2;
			}
			else if (map->map_r[map_y][map_x + 1] == '0' && side == 1)
			{
				ray->side = 1;
			}
			else if (map->map_r[map_y][map_x - 1] == '0' && side == 1)
			{
				ray->side = 3;
			}
			else
				ray->side = 4;
		}
		ray->dist = cos((ray->rad - (scene->player).rad) * PI / 180.0) * ray->dist;
	}
	return (1);
}
/*
int		ray_casting(t_ray *ray, t_map *map, t_scene *scene)
{
	double		ty;
	double		dx;
	double		dy;
	double		x;
	double		y;
	int			flag;
	int			pos;
	double		temp_x;
	double		temp_y;

	x = floor(ray->pos_x);
	y = floor(ray->pos_y);
	if (is_ray_inf(ray))
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			pos = (int)(y * map->width_r + x);
			(map->data)[pos] = ray->color;
			y += ray->dydx;
		}
		return (0);
	}
	dx = (ray->rad >= 90.0 && ray->rad <= 270.0) ? -1.0 : 1.0;
	dy = (ray->rad >= 0.0 && ray->rad <= 180.0) ? 1.0 : -1.0;
	if (ray->dydx > 1.0 && ray->rad <= 90.0)
	{
		// check_vertical
		flag = 0;
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				pos = (int)(y * map->width_r + x);
				(map->data)[pos] = ray->color;
				y += dy;
			}
			temp_x = x + dx;
			temp_y = ray->dydx * (temp_x + dx - ray->pos_x) + ray->pos_y;
			if (is_hit(ray, temp_x, temp_y, map, scene))
				return (0);
			temp_y = y + dy;
			temp_x = ((temp_y - ray->pos_y) / ray->dydx) + ray->pos_x;
			if (is_hit(ray, temp_x, temp_y, map, scene))
				return (0);
			x += dx;
			y = temp_y;
		}
		// check_horizontal
	}
	else if (ray->dydx < -1.0 && ray->rad <= 180.0)
	{
		
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y < ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				pos = (int)(y * map->width_r + x);
				(map->data)[pos] = ray->color;
				y += dy;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			y += dy;
			x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		}
	}
	else if (ray->dydx > 1.0 && ray->rad <= 270.0)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x - 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				pos = (int)(y * map->width_r + x);
				(map->data)[pos] = ray->color;
				y += dy;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else if (ray->dydx < -1.0 && ray->rad <= 360.0)
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			ty = ray->dydx * ((x + 1) - ray->pos_x) + ray->pos_y;
			while (y > ty)
			{
				if (is_hit(ray, x, y, map, scene))
					return (0);
				pos = (int)(y * map->width_r + x);
				(map->data)[pos] = ray->color;
				y += dy;
			}
			x += dx;
			y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
		}
	}
	else
	{
		while (!is_hit(ray, x, y, map, scene))
		{
			pos = (int)(y * map->width_r + x);
			(map->data)[pos] = ray->color;
			//x += dx;
			//y = ray->dydx * (x - ray->pos_x) + ray->pos_y;
			y += dy;
			x = ((y - ray->pos_y) / ray->dydx) + ray->pos_x;
		}
	}
	return (0);
}
*/