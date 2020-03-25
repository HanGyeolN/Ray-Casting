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
t_ray		rays[N_RAY];
t_player	player;

void	init_map(t_map *map)
{
	map->width = 10;
	map->height = 10;
	map->color = 0xFFFFFF;
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
	int		dy;
	int		dx;

	i = 0;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		dx = (key == KEY_A) ? -1 : 1;
		dy = (key == KEY_W) ? -1 : 1;
		while (i < N_RAY)
		{
			(player.rays[i]).color = 0x000000;
			render_ray(window, &(player.rays[i]), map);
			i++;
		}
		i = -1;
		if (key == KEY_W || key == KEY_S)
		{
			while (++i < N_RAY)
				(player.rays[i]).pos_y += dy;
		}
		else if (key == KEY_A || key == KEY_D)
		{
			while (++i < N_RAY)
				(player.rays[i]).pos_x += dx;
		}
		i = -1;
		while (++i < N_RAY)
		{
			(player.rays[i]).color = 0xFFFFFF;
			render_ray(window, &(player.rays[i]), map);
			render_wall(window, &(player.rays[i]), i);
		}
	}
	printf("%d\n", key);
	return (0);
}

void	init_window(t_window *window, int width, int height, char *title, int gw)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width + gw, height, title);
	window->width = width;
	window->height = height;
	window->gw = gw;
	window->gh = height;
}

void	init_ray(t_ray *ray, double x, double y, double rad)
{
	ray->color = 0xFFFFFF;
	ray->pos_x = x;
	ray->pos_y = y;
	ray->rad = rad;
	if (ray->rad >= 88 && ray->rad <= 92)
		ray->dydx = 1;
	else if (ray->rad >= 268 && ray->rad <= 272)
		ray->dydx = -1;
	else
		ray->dydx = tan(ray->rad * PI / 180.0);
}

void	init_player(t_player *player, int x, int y)
{
	int		i;

	i = 0;
	player->pos_x = (double)x;
	player->pos_y = (double)y;
	while (i < N_RAY)
	{
		init_ray(&(player->rays[i]), (double)x, (double)y, 240.0 + ((60.0 / (N_RAY - 1)) * i));
		i++;
	}
}

int		main(void)
{
	int			i;

	i = 0;
	if (!(window = malloc(sizeof(t_window))) || 
		!(map = malloc(sizeof(t_map))))
		return (0);
	init_window(window, 200, 200, "title_test", 200);
	init_map(map);
	render_map(window, map);
	init_player(&player, 150, 150);
	while (i < N_RAY)
	{
		render_ray(window, &(player.rays[i]), map);
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		render_wall(window, &(player.rays[i]), i);
		i++;
	}
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
