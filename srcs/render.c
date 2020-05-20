#include "raycasting.h"
#include <stdio.h>

void	render(t_scene *scene)
{
	mlx_put_image_to_window((scene->window).mlx_ptr, (scene->window).win_ptr, (scene->window).img_ptr, 0, 0);
}