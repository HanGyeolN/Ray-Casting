#include "raycasting.h"
#include <stdio.h>

int		deal_key(int key, t_scene *scene)
{
	int		i;
	int		n_ray;
	double	temp;

	i = -1;
	n_ray = (int)(scene->window).width;
	ray_casting(&((scene->player).rays), &(scene->map), scene);
	// while (++i < n_ray)
	// {
	// 	((scene->player).rays[i]).color = 0x000000;
	// 	convert_3d(&(scene->window), &((scene->player).rays[i]), i, 'd', scene);
	// 	ray_casting(&((scene->player).rays[i]), &(scene->map), scene);
	// }
	i = -1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
	{
		if (key == KEY_W)
		{
			(scene->player).pos_x += cos((scene->player).rad * PI / 180.0) / 2.0;
			(scene->player).pos_y += sin((scene->player).rad * PI / 180.0) / 2.0;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		if (key == KEY_S)
		{
			(scene->player).pos_x -= cos((scene->player).rad * PI / 180.0) / 2.0;
			(scene->player).pos_y -= sin((scene->player).rad * PI / 180.0) / 2.0;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_D)
		{
			(scene->player).pos_x -= sin(((scene->player).rad) * PI / 180.0) / 2.0;
			(scene->player).pos_y += cos(((scene->player).rad) * PI / 180.0) / 2.0;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
		else if (key == KEY_A)
		{
			(scene->player).pos_x += sin(((scene->player).rad) * PI / 180.0) / 2.0;
			(scene->player).pos_y -= cos(((scene->player).rad) * PI / 180.0) / 2.0;
			while (++i < n_ray)
			{
				((scene->player).rays[i]).pos_x = (scene->player).pos_x;
				((scene->player).rays[i]).pos_y = (scene->player).pos_y;
			}
		}
	}
	else if (key == KEY_LEFT || key == KEY_RIGHT)
	{
		temp = (key == KEY_LEFT) ? -SPEED_ROT : SPEED_ROT;
		(scene->player).rad += temp;
		if ((scene->player).rad >= 360.0)
			(scene->player).rad -= 360.0;
		else if ((scene->player).rad < 0.0)
			(scene->player).rad += 360.0;
		while (++i < n_ray)
		{
			((scene->player).rays[i]).rad += temp;
			if (((scene->player).rays[i]).rad >= 360.0)
				((scene->player).rays[i]).rad -= 360.0;
			else if (((scene->player).rays[i]).rad < 0.0)
				((scene->player).rays[i]).rad += 360.0;
		}
	}
	i = -1;
	ray_casting(&((scene->player).rays), &(scene->map), scene);
	// while (++i < n_ray)
	// {
	// 	((scene->player).rays[i]).color = 0xFFFFFF;
	// 	ray_casting(&((scene->player).rays[i]), &(scene->map), scene);
	// 	convert_3d(&(scene->window), &((scene->player).rays[i]), i, 'a', scene);
	// }
	render(scene);
	return (0);
}