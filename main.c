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

t_window	*window;
t_map		*map;
t_ray		rays[36];

void	init_map(t_map *map)
{
	map->width = 10;
	map->height = 10;
	map->color = 0xAAAAAA;
	map->block_w = (int)(window->width / map->width);
	map->block_h = (int)(window->height / map->height);
	strcpy(map->map[0], "1111111111");
	strcpy(map->map[1], "1001000001");
	strcpy(map->map[2], "1001111001");
	strcpy(map->map[3], "1000000001");
	strcpy(map->map[4], "1111000001");
	strcpy(map->map[5], "1000000001");
	strcpy(map->map[6], "1101111001");
	strcpy(map->map[7], "1000010001");
	strcpy(map->map[8], "1000010001");
	strcpy(map->map[9], "1111111111");
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	int		i;

	i = 0;
	if (key == KEY_W)
	{
		while (i < 36)
		{
			rays[i].color = 0x000000;
			render_ray(window, &rays[i], map);
			i++;
		}
		i = 0;
		while (i < 36)
		{
			rays[i].pos_y -= 1;
			rays[i].color = 0xFFFFFF;
			render_ray(window, &rays[i], map);
			i++;
		}
	}
	printf("%d\n", key);
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
	ray->hit = 0;
	ray->color = 0xAAFFAA;
	ray->pos_x = x;
	ray->pos_y = y;
	ray->rad = rad;
	if (ray->rad >= 87.5 && ray->rad <= 92.5)
		ray->dydx = 1;
	else if (ray->rad >= 267.5 && ray->rad <= 272.5)
		ray->dydx = -1;
	else
		ray->dydx = tan(ray->rad * PI / 180.0);
}

int		main(void)
{
	int			i;

	if (!(window = malloc(sizeof(t_window))) || !(map = malloc(sizeof(t_map))))
		return (0);
	init_window(window, 640, 420, "title_test");
	init_map(map);
	render_map(window, map);
	i = 0;
	while (i < 36)
	{
		init_ray(&rays[i], 520, 230, (360 / 36) * i);
		render_ray(window, &rays[i], map);
		i++;
	}
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
