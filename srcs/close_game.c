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
	scene->map.map = 0;
	free(scene->map.map);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.n);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.s);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.w);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.e);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.f);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.c);
	mlx_destroy_image(scene->window.mlx_ptr,scene->texture.i);
	mlx_destroy_image(scene->window.mlx_ptr, scene->window.img_ptr);
	mlx_destroy_window(scene->window.mlx_ptr, scene->window.win_ptr);
	mlx_clear_window(scene->window.mlx_ptr, scene->window.win_ptr);
	free(scene->window.mlx_ptr);
	exit (0);
}