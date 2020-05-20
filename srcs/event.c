#include "raycasting.h"
#include <stdio.h>

int		press_key(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		close_game(scene);
	else if (key == KEY_W)
		move_front(&scene->map, &scene->player);
	else if (key == KEY_S)
		move_back(&scene->map, &scene->player);
	else if (key == KEY_D)
		move_right(&scene->map, &scene->player);
	else if (key == KEY_A)
		move_left(&scene->map, &scene->player);
	else if (key == KEY_RIGHT)
		rotate_right(&scene->player);
	else if (key == KEY_LEFT)
		rotate_left(&scene->player);
	ray_casting(&(scene->map), scene);
	render(scene);
	return (0);
}