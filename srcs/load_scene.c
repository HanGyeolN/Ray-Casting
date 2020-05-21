#include "raycasting.h"

int		load_scene(char *scene_path, t_scene *scene, t_cub *cub)
{
	int		len;

	len = ft_strlen(scene_path);
	if (ft_strcmp(&scene_path[len - 4], ".cub") != 0)
		return (0);
	parse_scene(scene_path, cub);
	scene->f_color = cub->color_f;
	scene->c_color = cub->color_c;
	init_window(&(scene->window), cub->res_w, cub->res_h, "cub3d");
	init_map(&(scene->map), cub);
	init_texture(scene->window.mlx_ptr, &(scene->texture), cub);
	if (!(init_sprite(&(scene->map), scene)))
		return (0);
	if (!(init_player(&(scene->player), cub)))
		return (0);
	return (1);
}