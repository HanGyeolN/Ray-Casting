/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:03:33 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:14:48 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	set_wall_distance(t_player *p, t_ray *r, t_map *map)
{
	int		map_x;
	int		map_y;
	int		hit;

	hit = 0;
	map_x = (int)p->pos_x;
	map_y = (int)p->pos_y;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			map_y += r->step_y;
			r->side = 1;
		}
		if (map->map[map_y][map_x] == '1')
			hit = 1;
	}
	set_wall_perp_distance(p, r, map_x, map_y);
}

void	set_ray_distance(t_scene *scene, int x)
{
	t_ray	*r;

	r = &(scene->player.rays[x]);
	r->line_h = (int)(scene->window.height / (r->perp_wall_dist));
	r->draw_s = -(r->line_h) / 2 + scene->window.height / 2;
	if (r->draw_s < 0)
		r->draw_s = 0;
	r->draw_e = r->line_h / 2 + scene->window.height / 2;
	if (r->draw_e >= scene->window.height)
		r->draw_e = scene->window.height - 1;
	r->wall_x = (r->side == 0) ? \
		(scene->player.pos_y + r->perp_wall_dist * r->dir_y) :
		(scene->player.pos_x + r->perp_wall_dist * r->dir_x);
	r->wall_x -= floor(r->wall_x);
}

void	set_ray_cardinal(t_scene *scene, int x)
{
	t_ray	*ray;

	ray = &(scene->player.rays[x]);
	if (ray->side == 1 && ray->dir_y >= 0)
		ray->cardinal = 0;
	else if (ray->side == 1 && ray->dir_y < 0)
		ray->cardinal = 2;
	else if (ray->side == 0 && ray->dir_x >= 0)
		ray->cardinal = 3;
	else if (ray->side == 0 && ray->dir_x < 0)
		ray->cardinal = 1;
}

void	set_fc_color(t_scene *scene, int x)
{
	int			y;
	t_window	*win;

	y = -1;
	win = &(scene->window);
	while (++y < scene->player.rays[x].draw_s)
		win->img_data[y * (int)win->width + x] = scene->c_color;
	y = scene->player.rays[x].draw_e - 1;
	while (++y < win->height)
		win->img_data[y * (int)win->width + x] = scene->f_color;
}

void	wall_casting(t_scene *scene)
{
	t_map	*map;
	int		x;

	map = &(scene->map);
	x = -1;
	while (++x < scene->window.width)
	{
		set_player_screen(scene, x);
		set_side_distance(scene, x);
		set_step_xy(scene, x);
		set_wall_distance(&(scene->player), &(scene->player.rays[x]), map);
		set_ray_cardinal(scene, x);
		set_ray_distance(scene, x);
		set_wall_texture(scene, x);
		set_fc_color(scene, x);
		scene->z_buffer[x] = scene->player.rays[x].perp_wall_dist;
	}
}
