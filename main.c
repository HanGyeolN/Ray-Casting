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
#include "libft.h"

void	init_map(t_map *map)
{
	map->map = make_map("test01.map", map);
	map->color = 0xFFFFFF;
	map->block_w = (int)(MAP_VIEW_W / map->width);
	map->block_h = (int)(MAP_VIEW_H / map->height);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		deal_key(int key, void *param)
{
	int		i;
	double	dy;
	double	dx;
	double	temp;
	double	a;

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
		if (key == KEY_W)
		{
			player.pos_x += cos(player.rad * PI / 180.0);
			player.pos_y += sin(player.rad * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		if (key == KEY_S)
		{
			player.pos_x -= cos(player.rad * PI / 180.0);
			player.pos_y -= sin(player.rad * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		else if (key == KEY_D)
		{
			player.pos_x -= sin((player.rad) * PI / 180.0);
			player.pos_y += cos((player.rad) * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
		else if (key == KEY_A)
		{
			player.pos_x += sin((player.rad) * PI / 180.0);
			player.pos_y -= cos((player.rad) * PI / 180.0);
			while (++i < N_RAY)
			{
				(player.rays[i]).pos_x = (int)player.pos_x;
				(player.rays[i]).pos_y = (int)player.pos_y;
			}
		}
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		temp = (key == KEY_LEFT) ? -SPEED_ROT : SPEED_ROT;
		player.rad += temp;
		if (player.rad >= 360.0)
			player.rad -= 360.0;
		else if (player.rad < 0.0)
			player.rad += 360.0;
		while (++i < N_RAY)
		{
			(player.rays[i]).rad += temp;
			if ((player.rays[i]).rad >= 360.0)
				(player.rays[i]).rad -= 360.0;
			else if ((player.rays[i]).rad < 0.0)
				(player.rays[i]).rad += 360.0;
			if ((player.rays[i]).rad >= 89.9 && (player.rays[i]).rad <= 90.1)
				(player.rays[i]).dydx = 1;
			else if ((player.rays[i]).rad >= 269.9 && (player.rays[i]).rad <= 270.1)
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
	render();
	return (0);
}

void	init_window(t_window *window, int width, int height, char *title)
{
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = (double)width;
	window->height = (double)height;
}

void	init_ray(t_ray *ray, double x, double y, double rad)
{
	ray->color = 0xFFFFFF;
	ray->pos_x = x;
	ray->pos_y = y;
	ray->rad = rad;
	if (is_ray_inf(ray) != 0)
		ray->dydx = (is_ray_inf(ray) == 1) ? 1 : -1;
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
	int			bpx, sl, en;

	i = 0;
	if (!(window = malloc(sizeof(t_window))) || 
		!(map = malloc(sizeof(t_map))))
		return (0);
	init_window(window, WIDTH, HEIGHT, "title_test");
	init_map(map);
	img_ptr1 = mlx_new_image(window->mlx_ptr, MAP_VIEW_W, MAP_VIEW_H);
	img_data1 = (int *)mlx_get_data_addr(img_ptr1, &bpx, &sl, &en);
	img_ptr2 = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	img_data2 = (int *)mlx_get_data_addr(img_ptr2, &bpx, &sl, &en);
	tx_img = mlx_png_file_to_image(window->mlx_ptr, "./textures/wall_50.png", &sl, &en);
	tx_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(tx_img, &bpx, &sl, &en);
	render_map(window, map);
	init_player(&player, (int)(MAP_VIEW_W * (2.0 / 3.0)), (int)(MAP_VIEW_H * (1.0 / 2.0)));
	while (i < N_RAY)
	{
		render_ray(window, &(player.rays[i]), map);
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		render_wall(window, &(player.rays[i]), i, 'a');
		i++;
	}
	render();
	mlx_hook(window->win_ptr, 2, 0, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
