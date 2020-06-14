#include "raycasting.h"

int		close_game(t_scene *scene)
{
	int		i;

	free(scene->z_buffer);
	free(scene->sprite);
	free(scene->player.rays);
	i = -1;
	while (++i < scene->map.height + 1)
		free(scene->map.map[i]);
	free(scene->map.map);
	mlx_destroy_image(scene->window.mlx_ptr, scene->window.img_ptr);
	mlx_destroy_window(scene->window.mlx_ptr, scene->window.win_ptr);
	while (1)
		i += 1;
	exit (0);
}