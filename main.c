/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 04:06:30 by hna               #+#    #+#             */
/*   Updated: 2020/03/23 04:59:58 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include <math.h>
#include "stdio.h"
#include <string.h>
#define PI 3.14159265

typedef struct		s_map
{
	double	width;
	double	height;
	char	map[5][7];
}					t_map;

void	init_map(t_map *map)
{
	map->width = 6;
	map->height = 5;
	strcpy(map->map[0], "111111");
	strcpy(map->map[1], "100101");
	strcpy(map->map[2], "100001");
	strcpy(map->map[3], "110001");
	strcpy(map->map[4], "111111");
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	ft_putchar('X');
	return (0);
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

void	init_window(t_window *window, int width, int height, char *title)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = width;
	window->height = height;
}

void	init_ray(t_ray *ray)
{
	ray->pos_x = 300.0;
	ray->pos_y = 300.0;
	ray->rad = 90.0;
	if (ray->rad == 90.0)
		ray->deg_y = 1024;
	else
		ray->deg_y = tan(ray->rad * PI / 180.0);
	ray->deg_x = 1;
}

void	render_ray(t_window *window, t_ray *ray)
{
	double		x;
	double		y;
	double		temp_y;
	double		dydx;

	x = (double)ray->pos_x;
	y = (double)ray->pos_y;
	dydx = ray->deg_y / ray->deg_x;
	while ((x >= 0 && x < window->width) && (y >= 0 && y < window->height))
	{
		y = dydx * (x - ray->pos_x) + ray->pos_y;
		if (dydx > 1.0 || dydx < -1.0)
		{
			if (dydx > 0)
				temp_y = dydx * ((x - 1.0) - ray->pos_x) + ray->pos_y;
			else
				temp_y = dydx * ((x + 1.0) - ray->pos_x) + ray->pos_y;
			while (temp_y < y)
			{
				mlx_pixel_put(window->mlx_ptr, window->win_ptr, (int)x, (int)temp_y, 0xFFFFFF);
				temp_y++;
			}
		}
		else
			mlx_pixel_put(window->mlx_ptr, window->win_ptr, (int)x, (int)y, 0xFFFFFF);
		x++;
	}
}

int		main(void)
{
	t_window	*window;
	t_map		*map;
	t_ray		ray;

	if (!(window = malloc(sizeof(t_window))) || !(map = malloc(sizeof(t_map))))
		return (0);
	init_window(window, 400, 400, "title_test");
	init_map(map);
	init_ray(&ray);
	render_map(window, map);
	render_ray(window, &ray);
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
