#include "raycasting.h"

void	init_mlx_window(t_scene *scene, t_cub *cub, char *title)
{
	t_window	*wd;
	int			width;
	int			height;
	int			tp;

	width = cub->res_w;
	height = cub->res_h;
	wd = &(scene->window);
	wd->mlx_ptr = mlx_init();
	wd->win_ptr = mlx_new_window(wd->mlx_ptr, width, height, title);
	wd->width = (double)width;
	wd->height = (double)height;
	wd->img_ptr = mlx_new_image(wd->mlx_ptr, width, height);
	wd->img_data = (int *)mlx_get_data_addr(wd->img_ptr, &tp, &tp, &tp);
}

void	init_map(t_map *map, t_cub *cub)
{
	map->map = cub->map;
	map->color = 0xFFFFFF;
	map->width = (double)cub->map_w;
	map->height = (double)cub->map_h;
}

int		xpm_to_image(void **image, void *mlx, char *filepath)
{
	int		tp;

	if (!(*image = mlx_xpm_file_to_image(mlx, filepath, &tp, &tp)))
	{
		error("no such file | ");
		ft_printf(filepath);
		return (0);
	}
	return (1);
}

void	init_texture_data(t_texture *t)
{
	int		tp;

	t->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->n, &tp, &tp, &tp);
	t->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->s, &tp, &tp, &tp);
	t->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->w, &tp, &tp, &tp);
	t->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->e, &tp, &tp, &tp);
	t->i_data = (int(*)[SPRITE_W])mlx_get_data_addr(t->i, &tp, &tp, &tp);
	t->f_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->f, &tp, &tp, &tp);
	t->c_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->c, &tp, &tp, &tp);
}

int		init_texture(void *mlx_ptr, t_texture *tex, t_cub *cub)
{
	if (!(xpm_to_image(&(tex->n), mlx_ptr, cub->tex_n)))
		return (0);
	if (!(xpm_to_image(&(tex->s), mlx_ptr, cub->tex_s)))
		return (0);
	if (!(xpm_to_image(&(tex->w), mlx_ptr, cub->tex_w)))
		return (0);
	if (!(xpm_to_image(&(tex->e), mlx_ptr, cub->tex_e)))
		return (0);
	if (!(xpm_to_image(&(tex->i), mlx_ptr, cub->tex_i)))
		return (0);
	if (!(xpm_to_image(&(tex->f), mlx_ptr, "./textures/floor.xpm")))
		return (0);
	if (!(xpm_to_image(&(tex->c), mlx_ptr, "./textures/ceiling.xpm")))
		return (0);
	init_texture_data(tex);
	return (1);
}

int		init_player(t_player *player, t_cub *cub)
{
	player->pos_x = (double)cub->player_x + 0.5;
	player->pos_y = (double)cub->player_y + 0.5;
	player->rad = cub->player_dir;
	player->move_speed = 0.1;
	player->rot_speed = 0.08;
	player->plane_x = 0.0;
	player->plane_y = 0.66;
	player->dir_x = 1.0;
	player->dir_y = 0.0;
	rotate_player(player, (player->rad * PI / 180));
	rotate_plane(player, (player->rad * PI / 180));
	if (!(player->rays = malloc(sizeof(t_ray) * cub->res_w)))
		return (error("malloc failed | init_player"));
	return (1);
}