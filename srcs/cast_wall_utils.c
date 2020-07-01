/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:36:07 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:12:34 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	set_player_screen(t_scene *scene, int x)
{
	double		camera_x;
	t_window	*win;
	t_player	*p;

	win = &(scene->window);
	p = &(scene->player);
	camera_x = 2 * x / win->width - 1;
	p->rays[x].dir_x = p->dir_x + p->plane_x * camera_x;
	p->rays[x].dir_y = p->dir_y + p->plane_y * camera_x;
	p->rays[x].delta_dist_x = fabs(1 / p->rays[x].dir_x);
	p->rays[x].delta_dist_y = fabs(1 / p->rays[x].dir_y);
}

void	set_side_distance(t_scene *scene, int x)
{
	t_player	*p;
	t_ray		*r;

	p = &(scene->player);
	r = &(scene->player.rays[x]);
	if (r->dir_x < 0)
		r->side_dist_x = (p->pos_x - (int)p->pos_x) * r->delta_dist_x;
	else
		r->side_dist_x = ((int)p->pos_x + 1.0 - p->pos_x) * r->delta_dist_x;
	if (r->dir_y < 0)
		r->side_dist_y = (p->pos_y - (int)p->pos_y) * r->delta_dist_y;
	else
		r->side_dist_y = ((int)p->pos_y + 1.0 - p->pos_y) * r->delta_dist_y;
}

void	set_step_xy(t_scene *scene, int x)
{
	t_ray	*r;

	r = &(scene->player.rays[x]);
	if (r->dir_x < 0)
		r->step_x = -1;
	else
		r->step_x = 1;
	if (r->dir_y < 0)
		r->step_y = -1;
	else
		r->step_y = 1;
}

void	set_wall_perp_distance(t_player *p, t_ray *r, int map_x, int map_y)
{
	r->perp_wall_dist = (r->side == 0) ? \
			((map_x - p->pos_x + (1 - r->step_x) / 2) / r->dir_x) :
			((map_y - p->pos_y + (1 - r->step_y) / 2) / r->dir_y);
}
