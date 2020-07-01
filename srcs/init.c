/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:04:02 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:12:52 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_mlx_window(t_scene *scene, t_cub *cub, char *title)
{
	t_window	*wd;
	int			width;
	int			height;
	int			tp;

	width = cub->res_w;
	height = cub->res_h;
	wd = &(scene->window);
	wd->mlx_ptr = mlx_init();
	wd->win_ptr = mlx_new_window(wd->mlx_ptr, width, height, title);
	wd->width = (double)width;
	wd->height = (double)height;
	wd->img_ptr = mlx_new_image(wd->mlx_ptr, width, height);
	wd->img_data = (int *)mlx_get_data_addr(wd->img_ptr, &tp, &tp, &tp);
}

void	init_map(t_map *map, t_cub *cub)
{
	map->map = cub->map;
	map->color = 0xFFFFFF;
	map->width = (double)cub->map_w;
	map->height = (double)cub->map_h;
}

int		init_player(t_player *player, t_cub *cub)
{
	player->pos_x = (double)cub->player_x + 0.5;
	player->pos_y = (double)cub->player_y + 0.5;
	player->rad = cub->player_dir;
	player->move_speed = 0.1;
	player->rot_speed = 0.08;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	rotate_player(player, (player->rad * PI / 180));
	rotate_plane(player, (player->rad * PI / 180));
	if (!(player->rays = malloc(sizeof(t_ray) * cub->res_w)))
		return (error("malloc failed | init_player"));
	return (1);
}
