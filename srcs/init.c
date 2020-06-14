#include "raycasting.h"

void	init_window(t_window *window, int width, int height, char *title)
{
	int		tp;

	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = (double)width;
	window->height = (double)height;
	window->img_ptr = mlx_new_image(window->mlx_ptr, width, height);
	window->img_data = \
		(int *)mlx_get_data_addr(window->img_ptr, &tp, &tp, &tp);
}

void	init_map(t_map *map, t_cub *cub)
{
	map->map = cub->map;
	map->color = 0xFFFFFF;
	map->width = (double)cub->map_w;
	map->height = (double)cub->map_h;
}

void	init_texture(void *mlx_ptr, t_texture *t, t_cub *cub)
{
	int		tp;

	t->n = mlx_xpm_file_to_image(mlx_ptr, cub->tex_n, &tp, &tp);
	t->s = mlx_xpm_file_to_image(mlx_ptr, cub->tex_s, &tp, &tp);
	t->w = mlx_xpm_file_to_image(mlx_ptr, cub->tex_w, &tp, &tp);
	t->e = mlx_xpm_file_to_image(mlx_ptr, cub->tex_e, &tp, &tp);
	t->i = mlx_xpm_file_to_image(mlx_ptr, cub->tex_i, &tp, &tp);
	t->f = mlx_xpm_file_to_image(mlx_ptr, "./textures/floor.xpm", &tp, &tp);
	t->c = mlx_xpm_file_to_image(mlx_ptr, "./textures/ceiling.xpm", &tp, &tp);
	t->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->n, &tp, &tp, &tp);
	t->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->s, &tp, &tp, &tp);
	t->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->w, &tp, &tp, &tp);
	t->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->e, &tp, &tp, &tp);
	t->i_data = (int(*)[SPRITE_W])mlx_get_data_addr(t->i, &tp, &tp, &tp);
	t->f_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->f, &tp, &tp, &tp);
	t->c_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(t->c, &tp, &tp, &tp);
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
		return (0);
	return (1);
}