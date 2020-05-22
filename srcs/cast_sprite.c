#include "raycasting.h"

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i, j;
	int		temp;
	double	tp;

	i = 0;
	while (i < amount)
	{
		j = i + 1;
		while (j < amount)
		{
			if (dist[i] < dist[j])
			{
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
				tp = dist[i];
				dist[i] = dist[j];
				dist[j] = tp;
			}
			j++;
		}
		i++;
	}
}

void	sprite_casting(t_scene *scene)
{
	int		i;
	int		y;
	int		n_sprite;
	int		color;

	n_sprite = scene->n_sprite;
	i = 0;
	while (i < n_sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (scene->player.pos_x - scene->sprite[i].x) * (scene->player.pos_x - scene->sprite[i].x);
		sprite_distance[i] += (scene->player.pos_y - scene->sprite[i].y) * (scene->player.pos_y - scene->sprite[i].y);
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, n_sprite);
	i = 0;
	int		scale_w = 2;
	int		scale_h = 2;
	while (i < n_sprite)
	{
		if (scene->sprite[i].d == 1)
		{
			double	sprite_x, sprite_y;

			sprite_x = scene->sprite[sprite_order[i]].x - scene->player.pos_x;
			sprite_y = scene->sprite[sprite_order[i]].y - scene->player.pos_y;

			double	inv_det;
			inv_det = 1.0 / (scene->player.plane_x * scene->player.dir_y - scene->player.dir_x * scene->player.plane_y);

			double	trans_x, trans_y;
			trans_x = inv_det * (scene->player.dir_y * sprite_x - scene->player.dir_x * sprite_y);
			// trans_x = inv_det * (scene->player.dir_y * sprite_x + scene->player.plane_y * sprite_y);
			trans_y = inv_det * (-scene->player.plane_y * sprite_x + scene->player.plane_x * sprite_y);
			// trans_y = inv_det * (scene->player.dir_x * sprite_x - scene->player.plane_x * sprite_y);

			int		sprite_screen_x = (int)((scene->window.width / 2) * (1 + trans_x / trans_y));
			int		sprite_height = abs((int)(scene->window.height / trans_y) / scale_h);

			// calculate lowest and highest pixel to fill in curren stripe
			int		draw_start_y = -sprite_height / 2 + scene->window.height / 2;
			if (draw_start_y < 0)
				draw_start_y = 0;
			int		draw_end_y = sprite_height / 2 + scene->window.height / 2;
			if (draw_end_y >= scene->window.height)
				draw_end_y = scene->window.height - 1;
			
			// claculate width of the sprite
			int		sprite_width = abs((int)(scene->window.height / trans_y) / scale_w);
			int		draw_start_x = -sprite_width / 2 + sprite_screen_x;
			if (draw_start_x < 0)
				draw_start_x = 0;
			int		draw_end_x = sprite_width / 2 + sprite_screen_x;
			if (draw_end_x >= scene->window.width)
				draw_end_x = scene->window.width - 1;
			
			// vertical stripe
			int		d, stripe;
			stripe = draw_start_x;
			while (stripe < draw_end_x)
			{
				int		tex_x, tex_y;
				tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * SPRITE_W / sprite_width) / 256;
				if (trans_y > 0.5 && stripe > 0 && stripe < scene->window.width && trans_y < scene->z_buffer[stripe])
				{
					y = draw_start_y;
					while (y < draw_end_y)
					{
						d = y * 256 - (int)scene->window.height * 128 + sprite_height * 128;
						tex_y = ((d * SPRITE_H) / sprite_height) / 256;
						color = scene->texture.i_data[tex_y][tex_x];
						scene->window.img_data[y * (int)scene->window.width + stripe] = color;
						y++;
					}
				}
				stripe++;
			}
		}
		i++;
	}
}