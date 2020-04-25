#include "raycasting.h"
#include <stdio.h>

int		deal_key(int key, t_scene *scene)
{
	int		i;
	int		n_ray;

	i = -1;
	n_ray = (int)(scene->window).width;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		if (key == KEY_W)
		{
			printf("%f, %f\n", (scene->player).pos_x, (scene->player).pos_y);
			if (scene->map.map[(int)scene->player.pos_y][(int)(scene->player.pos_x + scene->player.dir_x * scene->player.move_speed)] != '1')
				scene->player.pos_x += scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)(scene->player.pos_y + scene->player.dir_y * scene->player.move_speed)][(int)scene->player.pos_x] != '1')
				scene->player.pos_y += scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				//printf("%d: %f, %f\n", i, ((scene->player).rays[i]).pos_x, ((scene->player).rays[i]).pos_y);
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
				//printf("%d: %f, %f\n", i, ((scene->player).rays[i]).pos_x, ((scene->player).rays[i]).pos_y);
			}
			printf("%f, %f\n", (scene->player).pos_x, (scene->player).pos_y);
		}
		if (key == KEY_S)
		{
			if (scene->map.map[(int)(scene->player.pos_x - scene->player.dir_x * scene->player.move_speed)][(int)scene->player.pos_y] != '1')
				scene->player.pos_x -= scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)scene->player.pos_x][(int)(scene->player.pos_y - scene->player.dir_y * scene->player.move_speed)] != '1')
				scene->player.pos_y -= scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_D)
		{
			if (scene->map.map[(int)(scene->player.pos_x - scene->player.dir_x * scene->player.move_speed)][(int)scene->player.pos_y] != '1')
				scene->player.pos_x -= scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)scene->player.pos_x][(int)(scene->player.pos_y + scene->player.dir_y * scene->player.move_speed)] != '1')
				scene->player.pos_y += scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_A)
		{
			if (scene->map.map[(int)(scene->player.pos_x + scene->player.dir_x * scene->player.move_speed)][(int)scene->player.pos_y] != '1')
				scene->player.pos_x += scene->player.dir_x * scene->player.move_speed;
			if (scene->map.map[(int)scene->player.pos_x][(int)(scene->player.pos_y - scene->player.dir_y * scene->player.move_speed)] != '1')
				scene->player.pos_y -= scene->player.dir_y * scene->player.move_speed;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
	}
	// else if (key == KEY_LEFT || key == KEY_RIGHT)
	// {
	// 	if (key == KEY_RIGHT)
	// 	{
	// 		scene->player.dir_x = scene->player.dir_x * cos(-(scene->player.rot_speed) - scene->player.dir_y)
	// 	}
	// }
	// while (++i < n_ray)
	// {
	// 	((scene->player).rays[i]).color = 0xFFFFFF;
	// 	ray_casting(&((scene->player).rays[i]), &(scene->map), scene);
	// 	convert_3d(&(scene->window), &((scene->player).rays[i]), i, 'a', scene);
	// }
	ray_casting(&((scene->player).rays), &(scene->map), scene);
	render(scene);
	printf("=========\n");
	return (0);
}