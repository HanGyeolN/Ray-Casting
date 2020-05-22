#include "raycasting.h"

void	floor_casting(t_scene *scene)
{
	float	ray_dir_x0, ray_dir_x1, ray_dir_y0, ray_dir_y1;
	int		p;
	int		color;
	int		x;
	int		y;
	float	pos_z;
	float	row_dist;
	float	f_stepx, f_stepy;
	float	floor_x, floor_y;
	int cell_x, cell_y;
	int	tx, ty;

	y = -1;
	while (++y < scene->window.height)
	{
		ray_dir_x0 = (scene->player.dir_x + scene->player.plane_x); // -1 0
		ray_dir_y0 = (scene->player.dir_y + scene->player.plane_y); // 0 0.66
		ray_dir_x1 = (scene->player.dir_x - scene->player.plane_x);
		ray_dir_y1 = (scene->player.dir_y - scene->player.plane_y);
		
		p = y - scene->window.height / 2;
	
		pos_z = 0.5 * scene->window.height;

		row_dist = pos_z / p;

		f_stepx = row_dist * (ray_dir_x1 - ray_dir_x0) / scene->window.width;
		f_stepy = row_dist * (ray_dir_y1 - ray_dir_y0) / scene->window.width;

		floor_x = scene->player.pos_x + row_dist * ray_dir_x0;
		floor_y = scene->player.pos_y + row_dist * ray_dir_y0;

		x = -1;
		while (++x < scene->window.width)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;

			// tx = (int)(TEXTURE_W * (floor_x - cell_x));
			// while (tx >= TEXTURE_W)
			// 	tx -= 1;
			// ty = (int)(TEXTURE_H * (floor_y - cell_y));
			// while (ty >= TEXTURE_H)
			// 	ty -= 1;

			//tx = (int)fabs((TEXTURE_W - 1) * (floor_x - cell_x));// & (TEXTURE_W - 1);
			//ty = (int)fabs((TEXTURE_H - 1) * (floor_y - cell_y));// & (TEXTURE_H - 1);
			
			tx = (int)(TEXTURE_W * (floor_x - cell_x));
			if (tx < 0 || tx > 50)
				tx = 0;
			ty = (int)(TEXTURE_H * (floor_y - cell_y));
			if (ty < 0 || ty > 50)
				ty = 0;
			floor_x += f_stepx;
			floor_y += f_stepy;
			color = scene->texture.f_data[ty][tx];
			scene->window.img_data[(int)(scene->window.width * y + ((int)scene->window.width - x - 1))] = color;
			color = scene->texture.c_data[ty][tx];
			scene->window.img_data[(int)(scene->window.width * ((int)scene->window.height - y - 1) + ((int)scene->window.width - x - 1))] = color;
		}
	}
}