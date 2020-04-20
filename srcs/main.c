/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 04:06:30 by hna               #+#    #+#             */
/*   Updated: 2020/03/23 04:59:58 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "stdio.h"
#include "libft.h"

void	init_map(t_window *window, t_map *map)
{
	int		tp;

	map->map = make_map("test01.map", map);
	map->color = 0xFFFFFF;
	map->block_w = (int)(MAP_VIEW_W / map->width);
	map->block_h = (int)(MAP_VIEW_H / map->height);
	map->image = mlx_new_image(window->mlx_ptr, MAP_VIEW_W, MAP_VIEW_H);
	map->data = (int *)mlx_get_data_addr(map->image, &tp, &tp, &tp);
}

void	init_window(t_window *window, int width, int height, char *title)
{
	int		tp;

	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, width, height, title);
	window->width = (double)width;
	window->height = (double)height;
	window->img_ptr = mlx_new_image(window->mlx_ptr, WIDTH, HEIGHT);
	window->img_data = \
		(int *)mlx_get_data_addr(window->img_ptr, &tp, &tp, &tp);
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

void	init_player(t_player *player, int x, int y)
{
	int		i;

	i = 0;
	player->pos_x = (double)x;
	player->pos_y = (double)y;
	player->rad = 270.0;
	while (i < N_RAY)
	{
		init_ray(&(player->rays[i]), 
					(double)x,
					(double)y,
					player->rad + ((60.0 / (N_RAY - 1)) * i) - 30.0);
		i++;
	}
}

void	init_texture(t_window *window, t_texture *txr)
{
	int		temp;

	txr->n = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/1.png", &temp, &temp);
	txr->s = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/2.png", &temp, &temp);
	txr->w = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/3.png", &temp, &temp);
	txr->e = mlx_png_file_to_image(window->mlx_ptr, \
		"./textures/4.png", &temp, &temp);
	txr->n_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->n, \
														&temp, &temp, &temp);
	txr->s_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->s, \
														&temp, &temp, &temp);
	txr->w_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->w, \
														&temp, &temp, &temp);
	txr->e_data = (int(*)[TEXTURE_SIZE])mlx_get_data_addr(txr->e, \
														&temp, &temp, &temp);
}
/*
int		parse_r(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] != ' ')
			i++;
		if (i )
	}
}

int		is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		parse_resolution(char *str)
{
	int		i;

	i = 2;
	if (ft_strncmp(str, "R ", 2) == 0)
	{
		ft_atoi(&str[2]);
		while (is_num(str[i]))
			i++;
		ft_atoi(&str[i]);
	}
	else if (ft_strcmp(str, "NO ", 3))
	{
		opt->txr_no_path = ft_strdup(&(str));
	}
}

int		get_options(char *filepath, t_option *opt)
{
	int		fd;
	int		len;
	char	*line;

	fd = open(filepath, O_RDONLY);
	while (len = get_next_line(fd, &line))
	{
		if (line[0] == 'R')
		{
			opt->res_w = ft_atoi(&line[2]);
		}
	}
}
*/
int		load_scene(char *filepath, t_scene *scene)
{
	init_window(&(scene->window), WIDTH, HEIGHT, filepath);
	init_map(&(scene->window), &(scene->map));
	init_texture(&(scene->window), &(scene->texture));
	put_map_to_img(&(scene->map));
	init_player(&(scene->player), (int)(MAP_VIEW_W * (2.0 / 3.0)), (int)(MAP_VIEW_H * (1.0 / 2.0)));
	return (1);
}

void	casting(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < N_RAY)
	{
		ray_casting(&(scene->player.rays[i]), &(scene->map), scene);
		i++;
	}
}

void	convert(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < N_RAY)
	{
		convert_3d(&(scene->window), &(scene->player.rays[i]), i, 'a', scene);
		i++;
	}
}

int		main(void)
{
	t_scene		scene;

	if (!(load_scene("./scene/test.cub", &scene)))
		return (-1);
	casting(&scene);
	convert(&scene);
	render(&scene);
	mlx_hook((scene.window).win_ptr, 2, 0, deal_key, &scene);
	mlx_loop((scene.window).mlx_ptr);
}