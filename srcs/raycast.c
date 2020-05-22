#include "raycasting.h"

int		ray_casting(t_scene *scene)
{
	// floor_casting(scene);
	wall_casting(scene);
	sprite_casting(scene);
	return (1);
}