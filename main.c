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
#include "stdio.h"
#include <string.h>

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

void	init_window(t_window *window, int width, int height, char *title)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = width;
	window->height = height;
}

void	init_ray(t_ray *ray, double x, double y, double rad)
{
	ray->pos_x = x;
	ray->pos_y = y;
	ray->rad = rad;
	if (ray->rad >= 89.5 && ray->rad <= 90.5)
		ray->dydx = 1;
	else if (ray->rad >= 269.5 && ray->rad <= 270.5)
		ray->dydx = -1;
	else
		ray->dydx = tan(ray->rad * PI / 180.0);
}

int		main(void)
{
	t_window	*window;
	t_map		*map;
	t_ray		ray[10];
	int			i;

	if (!(window = malloc(sizeof(t_window))) || !(map = malloc(sizeof(t_map))))
		return (0);
	init_window(window, 400, 400, "title_test");
	init_map(map);
	render_map(window, map);
	i = 0;
	while (i < 10)
	{
		init_ray(&ray[i], 300, 300, 240 + (60 / 10) * i);
		render_ray(window, &ray[i]);
		i++;
	}
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
