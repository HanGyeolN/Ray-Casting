#include "raycasting.h"
#include <stdio.h>

int		press_key(int key, t_scene *scene)
{
	int		i;
	int		n_ray;

	i = -1;
	n_ray = (int)(scene->window).width;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		if (key == KEY_W)
		{
			if (scene->map.map[(int)scene->player.pos_y][(int)(scene->player.pos_x + scene->player.dir_x * scene->player.move_speed)] != '1')
				scene->player.pos_x += scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)(scene->player.pos_y + scene->player.dir_y * scene->player.move_speed)][(int)scene->player.pos_x] != '1')
				scene->player.pos_y += scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		if (key == KEY_S)
		{
			if (scene->map.map[(int)scene->player.pos_y][(int)(scene->player.pos_x - scene->player.dir_x * scene->player.move_speed)] != '1')
				scene->player.pos_x -= scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)(scene->player.pos_y - scene->player.dir_y * scene->player.move_speed)][(int)scene->player.pos_x] != '1')
				scene->player.pos_y -= scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_D)
		{
			double	dir_x, dir_y;
			double	theta;
			theta = 90.0 * PI / 180;
			dir_x = scene->player.dir_x * cos(theta) - scene->player.dir_y * sin(theta);
			dir_y = scene->player.dir_x * sin(theta) + scene->player.dir_y * cos(theta);
			if (scene->map.map[(int)scene->player.pos_y][(int)(scene->player.pos_x + dir_x * scene->player.move_speed)] != '1')
				scene->player.pos_x += dir_x * scene->player.move_speed;
			if (scene->map.map[(int)(scene->player.pos_y + dir_y * scene->player.move_speed)][(int)scene->player.pos_x] != '1')
				scene->player.pos_y += dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_A)
		{
			double	dir_x, dir_y;
			double	theta;
			theta = -90.0 * PI / 180;
			dir_x = scene->player.dir_x * cos(theta) - scene->player.dir_y * sin(theta);
			dir_y = scene->player.dir_x * sin(theta) + scene->player.dir_y * cos(theta);
			if (scene->map.map[(int)scene->player.pos_y][(int)(scene->player.pos_x + dir_x * scene->player.move_speed)] != '1')
				scene->player.pos_x += dir_x * scene->player.move_speed;
			if (scene->map.map[(int)(scene->player.pos_y + dir_y * scene->player.move_speed)][(int)scene->player.pos_x] != '1')
				scene->player.pos_y += dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		if (key == KEY_RIGHT)
		{
			double old_dir_x, dir_x, dir_y, rot_speed;
			dir_x = scene->player.dir_x;
			dir_y = scene->player.dir_y;
			rot_speed = scene->player.rot_speed;
			old_dir_x = dir_x;
			dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
			dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);

			scene->player.dir_x = dir_x;
			scene->player.dir_y = dir_y;
			
			double old_plane_x, plane_x, plane_y;
			plane_x = scene->player.plane_x;
			plane_y = scene->player.plane_y;
			old_plane_x = plane_x;
			plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
			plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
			scene->player.plane_x = plane_x;
			scene->player.plane_y = plane_y;
		}
		else if (key == KEY_LEFT)
		{
			double old_dir_x, dir_x, dir_y, rot_speed;
			dir_x = scene->player.dir_x;
			dir_y = scene->player.dir_y;
			rot_speed = -scene->player.rot_speed;
			old_dir_x = dir_x;
			dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
			dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);

			scene->player.dir_x = dir_x;
			scene->player.dir_y = dir_y;
			
			double old_plane_x, plane_x, plane_y;
			plane_x = scene->player.plane_x;
			plane_y = scene->player.plane_y;
			old_plane_x = plane_x;
			plane_x = plane_x * cos(rot_speed) - plane_y * sin(rot_speed);
			plane_y = old_plane_x * sin(rot_speed) + plane_y * cos(rot_speed);
			scene->player.plane_x = plane_x;
			scene->player.plane_y = plane_y;
		}
	}
	ray_casting(&((scene->player).rays), &(scene->map), scene);
	render(scene);
	ft_printf("press_key : %d\n", key);
	return (0);
}

int		release_key(int key, t_scene *scene)
{
	if (!scene)
		return (0);
	ft_printf("release_key : %d\n", key);
	return (1);
}