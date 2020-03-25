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
	map->width = 10;
	map->height = 10;
	map->color = 0xFFFFFF;
	map->block_w = (window->width / map->width);
	map->block_h = (window->height / map->height);
	strcpy(map->map[0], "1111111111");
	strcpy(map->map[1], "1001000001");
	strcpy(map->map[2], "1001111101");
	strcpy(map->map[3], "1001111101");
	strcpy(map->map[4], "1101000001");
	strcpy(map->map[5], "1000000001");
	strcpy(map->map[6], "1101111001");
	strcpy(map->map[7], "1000001001");
	strcpy(map->map[8], "1000001001");
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
	double	temp;

	i = -1;
	while (++i < N_RAY)
	{
		(player.rays[i]).color = 0x000000;
		render_wall(window, &(player.rays[i]), i, 'd');
		render_ray(window, &(player.rays[i]), map);
	}
	i = -1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		dx = (key == KEY_A) ? -10 : 10;
		dy = (key == KEY_W) ? -10 : 10;
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
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		temp = (key == KEY_LEFT) ? -10 : 10;
		player.rad += temp;
		if (player.rad >= 360.0)
			player.rad -= 360.0;
		while (++i < N_RAY)
		{
			(player.rays[i]).rad += temp;
			if ((player.rays[i]).rad >= 360.0)
				(player.rays[i]).rad -= 360.0;
			if ((player.rays[i]).rad >= 88 && (player.rays[i]).rad <= 92)
				(player.rays[i]).dydx = 1;
			else if ((player.rays[i]).rad >= 268 && (player.rays[i]).rad <= 272)
				(player.rays[i]).dydx = -1;
			else
				(player.rays[i]).dydx = tan((player.rays[i]).rad * PI / 180.0);
		}
	}
	i = -1;
	while (++i < N_RAY)
	{
		(player.rays[i]).color = 0xFFFFFF;
		render_ray(window, &(player.rays[i]), map);
		render_wall(window, &(player.rays[i]), i, 'a');
	}
	printf("%d\n", key);
	return (0);
}

void	init_window(t_window *window, int width, int height, char *title, int gw)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width + gw, height, title);
	window->width = (double)width;
	window->height = (double)height;
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
	player->rad = 270.0;
	while (i < N_RAY)
	{
		init_ray(&(player->rays[i]), 
					(double)x,
					(double)y,
					player->rad + ((60.0 / (N_RAY - 1)) * i) - 30.0);
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
	init_window(window, 300, 300, "title_test", 300);
	init_map(map);
	render_map(window, map);
	init_player(&player, 200, 150);
	while (i < N_RAY)
	{
		render_ray(window, &(player.rays[i]), map);
		printf("ray %2d ", i);
		printf("hit: (%f, %f)\n", player.rays[i].hit_x, player.rays[i].hit_y);
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		render_wall(window, &(player.rays[i]), i, 'a');
		i++;
	}
	mlx_key_hook(window->win_ptr, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
