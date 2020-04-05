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

void	init_map(t_window *window, t_map *map)
{
	int		tp;

	map->map = make_map("test01.map", map);
	map->color = 0xFFFFFF;
	map->block_w = (int)(MAP_VIEW_W / map->width);
	map->block_h = (int)(MAP_VIEW_H / map->height);
	map->image = mlx_new_image(window->mlx_ptr, MAP_VIEW_W, MAP_VIEW_H);
	map->data = (int *)mlx_get_data_addr(map->image, &tp, &tp, &tp);
}

void	init_window(t_window *window, int width, int height, char *title)
{
	int		tp;

	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = (double)width;
	window->height = (double)height;
	window->img_ptr = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	window->img_data = \
		(int *)mlx_get_data_addr(window->img_ptr, &tp, &tp, &tp);
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

void	init_texture(t_window *window, t_texture *txr)
{
	int		temp;

	txr->n = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/wall_50.png", &temp, &temp);
	txr->s = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/wall_50.png", &temp, &temp);
	txr->w = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/wall_50.png", &temp, &temp);
	txr->e = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/wall_50.png", &temp, &temp);
	txr->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->n, \
														&temp, &temp, &temp);
	txr->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->s, \
														&temp, &temp, &temp);
	txr->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->w, \
														&temp, &temp, &temp);
	txr->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->e, \
														&temp, &temp, &temp);
}

int		main(void)
{
	int			i;

	i = 0;
	if (!(window = malloc(sizeof(t_window))) || 
		!(map = malloc(sizeof(t_map))) ||
		!(texture = malloc(sizeof(t_texture))))
		return (0);
	init_window(window, WIDTH, HEIGHT, "title_test");
	init_map(window, map);
	init_texture(window, texture);
	put_map_to_img(map);
	init_player(&player, (int)(MAP_VIEW_W * (2.0 / 3.0)), (int)(MAP_VIEW_H * (1.0 / 2.0)));
	while (i < N_RAY)
	{
		ray_casting(&(player.rays[i]), map);
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		convert_3d(window, &(player.rays[i]), i, 'a');
		i++;
	}
	render();
	mlx_hook(window->win_ptr, 2, 0, deal_key, (void *)0);
	mlx_loop(window->mlx_ptr);
}
