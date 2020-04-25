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
	map->block_w = 10;
	map->block_h = 10;
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
	ray->hit = 0;
	ray->hit_type = '0';
}

int		init_player(t_player *player, t_cub *cub, t_map *map)
{
	int		i;

	i = 0;
	if(!map)
		return (0);
	cub->player_x = cub->player_x;
	cub->player_y = cub->player_y;
	player->pos_x = (double)cub->player_x;
	player->pos_y = (double)cub->player_y;
	player->rad = cub->player_dir;
	player->dir_x = cos(player->rad * PI / 180); // -1
	player->dir_y = sin(player->rad * PI / 180); // 0
	printf("x, y : %f, %f\n", player->dir_x, player->dir_y);
	player->move_speed = 0.1;
	player->rot_speed = 0.1;
	player->plane_x = 0.0; //
	player->plane_y = 0.66; //
	double	old_plane_x, plane_x, plane_y;
	plane_x = player->plane_x;
	plane_y = player->plane_y;
	old_plane_x = plane_x;
	player->plane_x = plane_x * cos(player->rad * PI / 180) - plane_y * sin(player->rad * PI / 180);
	player->plane_y = old_plane_x * sin(player->rad * PI / 180) + plane_y * cos(player->rad * PI / 180);
	if (!(player->rays = malloc(sizeof(t_ray) * cub->res_w)))
		return (0);
	while (i < cub->res_w)
	{
		init_ray(&(player->rays[i]), 
					(double)cub->player_x,
					(double)cub->player_y,
					player->rad + ((60.0 / (double)(cub->res_w - 1)) * (double)i) - 30.0);
		i++;
	}
	return (1);
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
	scene->f_color = cub->color_f;
	scene->c_color = cub->color_c;
	init_window(&(scene->window), cub->res_w, cub->res_h, "cub3d");
	init_map(&(scene->window), &(scene->map), cub);
	if (!(new_map(&(scene->map))))
		return (0);
	init_texture(&(scene->window), &(scene->texture), cub);
	if (!(init_player(&(scene->player), cub, &(scene->map))))
		return (0);
	return (1);
}