/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:02:02 by hna               #+#    #+#             */
/*   Updated: 2020/06/29 15:03:32 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	set_sprite_xy(t_scene *s, t_spritev *sv)
{
	sv->v_move_screen = (int)(0.0 / sv->trans_y);
	sv->draw_start_y = -sv->sprite_height / 2 + s->window.height / 2 + \
						sv->v_move_screen;
	if (sv->draw_start_y < 0)
		sv->draw_start_y = 0;
	sv->draw_end_y = sv->sprite_height / 2 + s->window.height / 2 + \
						sv->v_move_screen;
	if (sv->draw_end_y >= s->window.height)
		sv->draw_end_y = s->window.height - 1;
	sv->draw_start_x = -(sv->sprite_width) / 2 + sv->sprite_screen_x;
	if (sv->draw_start_x < 0)
		sv->draw_start_x = 0;
	sv->draw_end_x = sv->sprite_width / 2 + sv->sprite_screen_x;
	if (sv->draw_end_x >= s->window.width)
		sv->draw_end_x = s->window.width - 1;
}

void	set_sprite_var(t_scene *s, t_spritev *sv, int *sprite_order, int i)
{
	t_player *p;
	t_window *w;

	p = &(s->player);
	w = &(s->window);
	sv->sprite_x = s->sprite[sprite_order[i]].x - p->pos_x;
	sv->sprite_y = s->sprite[sprite_order[i]].y - p->pos_y;
	sv->inv_det = 1.0 / (p->plane_x * p->dir_y - p->dir_x * p->plane_y);
	sv->trans_x = sv->inv_det * (p->dir_y * sv->sprite_x - \
					p->dir_x * sv->sprite_y);
	sv->trans_y = sv->inv_det * (-p->plane_y * sv->sprite_x + \
					p->plane_x * sv->sprite_y);
	sv->sprite_screen_x = (int)((w->width / 2) * \
					(1 + sv->trans_x / sv->trans_y));
	sv->scale_h = 1;
	sv->sprite_height = abs((int)(w->height / sv->trans_y) / sv->scale_h);
	sv->scale_w = 1;
	sv->sprite_width = abs((int)(w->height / sv->trans_y) / sv->scale_w);
	set_sprite_xy(s, sv);
}

void	draw_sprite(t_scene *s, t_spritev *sv)
{
	int			d;
	int			y;
	int			color;
	t_window	*w;

	y = sv->draw_start_y;
	w = &(s->window);
	while (y < sv->draw_end_y)
	{
		d = (y - sv->v_move_screen) * 256 - (int)w->height * 128 + \
			sv->sprite_height * 128;
		sv->tex_y = ((d * SPRITE_H) / sv->sprite_height) / 256;
		color = s->texture.i_data[sv->tex_y][sv->tex_x];
		if (color != 0)
			w->img_data[y * (int)w->width + sv->stripe] = color;
		y++;
	}
}

void	set_sprite_texture(t_scene *s, t_spritev *sv)
{
	sv->stripe = sv->draw_start_x;
	while (sv->stripe < sv->draw_end_x)
	{
		sv->tex_x = (int)(256 * (sv->stripe - (-(sv->sprite_width) / 2 + \
					sv->sprite_screen_x)) * SPRITE_W / sv->sprite_width) / 256;
		if (sv->trans_y > 0.5 && sv->stripe > 0 && sv->stripe < \
					s->window.width && sv->trans_y < s->z_buffer[sv->stripe])
		{
			draw_sprite(s, sv);
		}
		(sv->stripe)++;
	}
}

void	sprite_casting(t_scene *scene)
{
	int			i;
	int			*sprite_order;
	t_spritev	*sv;

	i = 0;
	sv = malloc(sizeof(t_spritev));
	sprite_order = get_sprite_order(scene);
	while (i < scene->n_sprite)
	{
		if (scene->sprite[i].d == 1)
		{
			set_sprite_var(scene, sv, sprite_order, i);
			set_sprite_texture(scene, sv);
		}
		i++;
	}
	free(sprite_order);
	free(sv);
}
