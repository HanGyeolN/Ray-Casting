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

void	init_map(t_window *window, t_map *map, t_cub *cub)
{
	int		tp;

	map->map = cub->map;
	map->color = 0xFFFFFF;
	map->width = (double)cub->map_w;
	map->height = (double)cub->map_h;
	map->block_w = 20;
	map->block_h = 20;
	map->width_r = map->block_w * cub->map_w;
	map->height_r = map->block_h * cub->map_h;
	map->image = mlx_new_image(window->mlx_ptr, map->width_r, map->height_r);
	map->data = (int *)mlx_get_data_addr(map->image, &tp, &tp, &tp);
	put_map_to_img(map);
}

void	init_texture(t_window *window, t_texture *txr, t_cub *cub)
{
	int		tp;

	txr->n = mlx_png_file_to_image(window->mlx_ptr, cub->tex_n, &tp, &tp);
	txr->s = mlx_png_file_to_image(window->mlx_ptr, cub->tex_s, &tp, &tp);
	txr->w = mlx_png_file_to_image(window->mlx_ptr, cub->tex_w, &tp, &tp);
	txr->e = mlx_png_file_to_image(window->mlx_ptr, cub->tex_e, &tp, &tp);
	txr->i = mlx_png_file_to_image(window->mlx_ptr, cub->tex_i, &tp, &tp);
	txr->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->n, \
														&tp, &tp, &tp);
	txr->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->s, \
														&tp, &tp, &tp);
	txr->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->w, \
														&tp, &tp, &tp);
	txr->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->e, \
														&tp, &tp, &tp);
	txr->i_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->i, \
														&tp, &tp, &tp);
}

void	init_ray(t_ray *ray, double x, double y, double rad)
{
	ray->color = 0xFFFFFF;
	ray->pos_x = x;
	ray->pos_y = y;
	ray->rad = rad;
	if (is_ray_inf(ray) != 0)
		ray->dydx = (is_ray_inf(ray) == 1) ? 1 : -1;
	else
		ray->dydx = tan(ray->rad * PI / 180.0);
}

void	init_player(t_player *player, t_cub *cub, t_map *map)
{
	int		i;

	i = 0;
	cub->player_x = cub->player_x * map->block_w + (map->block_w / 2);
	cub->player_y = cub->player_y * map->block_h + (map->block_h / 2);
	player->pos_x = (double)cub->player_x;
	player->pos_y = (double)cub->player_y;
	player->rad = (double)cub->player_dir;
	while (i < N_RAY)
	{
		init_ray(&(player->rays[i]), 
					(double)cub->player_x,
					(double)cub->player_y,
					player->rad + ((60.0 / (N_RAY - 1)) * i) - 30.0);
		i++;
	}
}

int		new_map(t_map *map)
{
	int		i;
	int		j;

	i = -1;
	if (!(map->map_r = malloc(sizeof(char *) * (map->height_r) + 1)))
		return (0);
	while (++i < map->height_r)
	{
		if (!(map->map_r[i] = malloc(sizeof(char) * (map->width_r) + 1)))
			return (0);
		map->map_r[i][(int)map->width_r] = 0;
	}
	map->map_r[i] = 0;
	i = -1;
	while (++i < map->height_r)
	{
		j = 0;
		while (j < map->width_r)
		{
			map->map_r[i][j] = map->map[i / map->block_h][j / map->block_w];
			j++;
		}
	}
	return (1);
}

int		load_scene(char *scene_path, t_scene *scene, t_cub *cub)
{
	parse_scene(scene_path, cub);
	init_window(&(scene->window), cub->res_w, cub->res_h, "cub3d");
	init_map(&(scene->window), &(scene->map), cub);
	if (!(new_map(&(scene->map))))
		return (0);
	init_texture(&(scene->window), &(scene->texture), cub);
	init_player(&(scene->player), cub, &(scene->map));
	return (1);
}