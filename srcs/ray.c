#include "raycasting.h"

int		ray_casting(t_ray **rays, t_map *map, t_scene *scene)
{
	int		x, y;
	int		map_x;
	int		map_y;
	double	camera_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		color;

	x = -1;
	y = -1;
	if (!rays)
		return (0);
	// floor casting
	float	ray_dir_x0, ray_dir_x1, ray_dir_y0, ray_dir_y1;
	int		p;
	float	pos_z;
	float	row_dist;
	float	f_stepx, f_stepy;
	float	floor_x, floor_y;
	int cell_x, cell_y;
	int	tx, ty;
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
			//printf("%d %d\n", ty, tx);
			floor_x += f_stepx;
			floor_y += f_stepy;
			//printf("%d, %d\n", ty, tx);
			color = scene->texture.f_data[ty][tx];
			//printf("texture[%d][%d]\n", ty, tx);
			//printf("%x\n", color);
			//color = (color >> 1) & 8355711;
			scene->window.img_data[(int)(scene->window.width * y + x)] = color;
			scene->window.img_data[(int)(scene->window.width * ((int)scene->window.height - y - 1) + x)] = color;
		}
	}

	// wall casting
	x = -1;
	y = -1;
	while (++x < scene->window.width)
	{
		hit = 0;
		camera_x = 2 * x / (double)scene->window.width - 1;
		scene->player.rays[x].dir_x = scene->player.dir_x + scene->player.plane_x * camera_x;
		scene->player.rays[x].dir_y = scene->player.dir_y + scene->player.plane_y * camera_x;
		map_x = (int)scene->player.rays[x].pos_x;
		map_y = (int)scene->player.rays[x].pos_y;
		scene->player.rays[x].delta_dist_x = fabs(1 / scene->player.rays[x].dir_x);
		scene->player.rays[x].delta_dist_y = fabs(1 / scene->player.rays[x].dir_y);

		if (scene->player.rays[x].dir_x < 0)
		{
			step_x = -1;
			scene->player.rays[x].side_dist_x = (scene->player.rays[x].pos_x - map_x) * scene->player.rays[x].delta_dist_x;
		}
		else
		{
			step_x = 1;
			scene->player.rays[x].side_dist_x = (map_x + 1.0 - scene->player.rays[x].pos_x) * scene->player.rays[x].delta_dist_x;
		}
		if (scene->player.rays[x].dir_y < 0)
		{
			step_y = -1;
			scene->player.rays[x].side_dist_y = (scene->player.rays[x].pos_y - map_y) * scene->player.rays[x].delta_dist_y;
		}
		else
		{
			step_y = 1;
			scene->player.rays[x].side_dist_y = (map_y + 1.0 - scene->player.rays[x].pos_y) * scene->player.rays[x].delta_dist_y;
		}

		// dda
		while (hit == 0)
		{
			if (scene->player.rays[x].side_dist_x < scene->player.rays[x].side_dist_y)
			{
				scene->player.rays[x].side_dist_x += scene->player.rays[x].delta_dist_x;
				map_x += step_x;
				scene->player.rays[x].side = 0;
			}
			else
			{
				scene->player.rays[x].side_dist_y += scene->player.rays[x].delta_dist_y;
				map_y += step_y;
				scene->player.rays[x].side = 1;
			}
			if (map->map[map_y][map_x] == '1')
			{
				hit = 1;
				scene->player.rays[x].hit_type = '1';
			}
		}

		// cardinal calc
		if (scene->player.rays[x].side == 1 && scene->player.rays[x].dir_y >= 0)
			scene->player.rays[x].cardinal = 0;
		else if (scene->player.rays[x].side == 1 && scene->player.rays[x].dir_y < 0)
			scene->player.rays[x].cardinal = 2;
		else if (scene->player.rays[x].side == 0 && scene->player.rays[x].dir_x >= 0)
			scene->player.rays[x].cardinal = 3;
		else if (scene->player.rays[x].side == 0 && scene->player.rays[x].dir_x < 0)
			scene->player.rays[x].cardinal = 1;
		
		// drawing
		scene->player.rays[x].perp_wall_dist = (scene->player.rays[x].side == 0) ? \
			((map_x - scene->player.rays[x].pos_x + (1 - step_x) / 2) / scene->player.rays[x].dir_x) :
			((map_y - scene->player.rays[x].pos_y + (1 - step_y) / 2) / scene->player.rays[x].dir_y);
		scene->player.rays[x].line_h = (int)(scene->window.height / (scene->player.rays[x].perp_wall_dist));
		scene->player.rays[x].draw_s = -(scene->player.rays[x].line_h) / 2 + scene->window.height / 2;
		if (scene->player.rays[x].draw_s < 0)
			scene->player.rays[x].draw_s = 0;
		scene->player.rays[x].draw_e = scene->player.rays[x].line_h / 2 + scene->window.height / 2;
		if (scene->player.rays[x].draw_e >= scene->window.height)
			scene->player.rays[x].draw_e = scene->window.height - 1;
		scene->player.rays[x].wall_x = (scene->player.rays[x].side == 0) ? \
			(scene->player.rays[x].pos_y + scene->player.rays[x].perp_wall_dist * scene->player.rays[x].dir_y) :
			(scene->player.rays[x].pos_x + scene->player.rays[x].perp_wall_dist * scene->player.rays[x].dir_x);
		scene->player.rays[x].wall_x -= floor(scene->player.rays[x].wall_x);

		// texture
		int		tex_x;
		tex_x = (int)(scene->player.rays[x].wall_x * (double)TEXTURE_W);
		if (scene->player.rays[x].side == 0 && scene->player.rays[x].dir_x > 0)
			tex_x = TEXTURE_W - tex_x - 1;
		if (scene->player.rays[x].side == 1 && scene->player.rays[x].dir_y < 0)
			tex_x = TEXTURE_W - tex_x - 1;
		
		double	step;
		step = 1.0 * TEXTURE_H / scene->player.rays[x].line_h;
		double	tex_pos;
		tex_pos = (scene->player.rays[x].draw_s - scene->window.height / 2 + scene->player.rays[x].line_h / 2) * step;
		y = scene->player.rays[x].draw_s - 1;
		while (++y < scene->player.rays[x].draw_e)
		{
			int		tex_y;
			tex_y = y * 256 - (int)scene->window.height * 128 + scene->player.rays[x].line_h * 128;
			tex_y = ((tex_y * TEXTURE_H) / scene->player.rays[x].line_h) / 256;
			if (scene->player.rays[x].cardinal == 0)
				color = scene->texture.n_data[tex_y][tex_x];
			else if (scene->player.rays[x].cardinal == 1)
				color = scene->texture.e_data[tex_y][tex_x];
			else if (scene->player.rays[x].cardinal == 2)
				color = scene->texture.s_data[tex_y][tex_x];
			else if (scene->player.rays[x].cardinal == 3)
				color = scene->texture.w_data[tex_y][tex_x];
			if (scene->player.rays[x].side == 1)
				color = (color >> 1) & 8355711;
			scene->window.img_data[y * (int)scene->window.width + ((int)scene->window.width - x - 1)] = color;
		}
		// floor color
		// y = -1;
		// while (++y < scene->player.rays[x].draw_s)
		// {
		// 	scene->window.img_data[y * (int)scene->window.width + ((int)scene->window.width - x - 1)] = scene->c_color;
		// }
		// y = scene->player.rays[x].draw_e - 1;
		// while (++y < scene->window.height)
		// {
		// 	scene->window.img_data[y * (int)scene->window.width + ((int)scene->window.width - x - 1)] = scene->f_color;
		// }
	}

	// printf("---------------------------------------------\n");
	// printf("pos: %f, %f\n", scene->player.rays[0].pos_x, scene->player.rays[0].pos_y);
	// printf("spd: %f\n", scene->player.move_speed);
	// printf("dist: %f\n", scene->player.rays[0].perp_wall_dist);
	// printf("dir: %f, %f\n", scene->player.rays[0].dir_x, scene->player.rays[0].dir_x);
	// printf("map: %d, %d\n", map_x, map_y);
	// printf("side: %f, %f\n", scene->player.rays[0].side_dist_x, scene->player.rays[0].side_dist_y);
	// printf("step: %d, %d\n", step_x, step_y);
	// printf("----------------------------------------------\n");
	return (1);
}