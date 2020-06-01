#include "raycasting.h"

void	set_fc_steps(t_scene *scene, t_floor *f)
{
	float	ray_dir_x0;
	float	ray_dir_x1;
	float	ray_dir_y0;
	float	ray_dir_y1;

	ray_dir_x0 = (scene->player.dir_x + scene->player.plane_x);
	ray_dir_y0 = (scene->player.dir_y + scene->player.plane_y);
	ray_dir_x1 = (scene->player.dir_x - scene->player.plane_x);
	ray_dir_y1 = (scene->player.dir_y - scene->player.plane_y);
	f->f_stepx = f->row_dist * (ray_dir_x1 - ray_dir_x0) / scene->window.width;
	f->f_stepy = f->row_dist * (ray_dir_y1 - ray_dir_y0) / scene->window.width;
	f->floor_x = scene->player.pos_x + f->row_dist * ray_dir_x0;
	f->floor_y = scene->player.pos_y + f->row_dist * ray_dir_y0;
}

void	set_fc_distance(t_scene *scene, t_floor *f, int y)
{
	int		p;
	float	pos_z;

	p = y - scene->window.height / 2;
	pos_z = 0.5 * scene->window.height;
	f->row_dist = pos_z / p;
}

void	set_fc_texture(t_scene *scene, t_floor *f, int y, int x)
{
	int		tx;
	int		ty;
	int		color;
	int		w;
	int		h;

	w = (int)scene->window.width;
	h = (int)scene->window.height;
	tx = (int)(TEXTURE_W * (f->floor_x - (int)f->floor_x));
	if (tx < 0 || tx > 50)
		tx = 0;
	ty = (int)(TEXTURE_H * (f->floor_y - (int)f->floor_y));
	if (ty < 0 || ty > 50)
		ty = 0;
	f->floor_x += f->f_stepx;
	f->floor_y += f->f_stepy;
	color = scene->texture.f_data[ty][tx];
	scene->window.img_data[(int)(w * y + (w - x - 1))] = color;
	color = scene->texture.c_data[ty][tx];
	scene->window.img_data[(int)(w * (h - y - 1) + (w - x - 1))] = color;
}

void	floor_casting(t_scene *scene)
{
	int		x;
	int		y;
	t_floor	floor;

	y = -1;
	while (++y < scene->window.height)
	{
		set_fc_distance(scene, &floor, y);
		set_fc_steps(scene, &floor);
		x = -1;
		while (++x < scene->window.width)
			set_fc_texture(scene, &floor, y, x);
	}
}