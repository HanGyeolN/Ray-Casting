/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_wall_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:32:06 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:12:43 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		get_color_by_cardinal(int cardinal, int x, int y, t_texture *t)
{
	int		color;

	color = 0;
	if (cardinal == 0)
		color = t->n_data[y][x];
	else if (cardinal == 1)
		color = t->e_data[y][x];
	else if (cardinal == 2)
		color = t->s_data[y][x];
	else if (cardinal == 3)
		color = t->w_data[y][x];
	return (color);
}

void	draw_wall(t_scene *scene, int x, int tex_x)
{
	int		y;
	int		color;
	int		tex_y;
	t_ray	*ray;

	ray = &(scene->player.rays[x]);
	y = ray->draw_s - 1;
	while (++y < ray->draw_e)
	{
		tex_y = y * 256 - (int)scene->window.height * 128 + ray->line_h * 128;
		tex_y = ((tex_y * TEXTURE_H) / ray->line_h) / 256;
		color = get_color_by_cardinal(ray->cardinal, \
									tex_x, tex_y, &scene->texture);
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		scene->window.img_data[y * (int)scene->window.width + (x)] = color;
	}
}

void	set_wall_texture(t_scene *scene, int x)
{
	int		tex_x;

	tex_x = (int)(scene->player.rays[x].wall_x * (double)TEXTURE_W);
	if (scene->player.rays[x].side == 0 && scene->player.rays[x].dir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (scene->player.rays[x].side == 1 && scene->player.rays[x].dir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	draw_wall(scene, x, tex_x);
}
