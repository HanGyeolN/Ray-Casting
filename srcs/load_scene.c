#include "raycasting.h"

int		is_cub_file(char *scene_path)
{
	int		len;

	len = ft_strlen(scene_path);
	if (ft_strcmp(&scene_path[len - 4], ".cub") != 0)
		return (error("extension error"));
	return (1);
}

int		parse_cub_file(char *filepath, t_cub *cub)
{
	if (!(is_cub_file(filepath)))
		return (0);
	if (!(parse_scene(filepath, cub)))
		return (0);
	return (1);
}

void	init_floor_ceiling_color(t_scene *scene, t_cub *cub)
{
	scene->f_color = cub->color_f;
	scene->c_color = cub->color_c;
}

int		init_scene(t_scene *scene, t_cub *cub)
{
	init_floor_ceiling_color(scene, cub);
	init_mlx_window(scene, cub, "cub3d");
	init_map(&(scene->map), cub);
	if (!(init_texture(scene->window.mlx_ptr, &(scene->texture), cub)))
		return (0);
	if (!(init_sprite(&(scene->map), scene)))
		return (0);
	if (!(init_player(&(scene->player), cub)))
		return (0);
	return (1);
}

int		load_scene(char *filepath, t_scene *scene)
{
	t_cub	cub;

	if (!(parse_cub_file(filepath, &cub)))
		return (0);
	if (!(init_scene(scene, &cub)))
		return (0);
	return (1);
}