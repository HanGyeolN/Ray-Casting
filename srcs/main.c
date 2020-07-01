/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 04:06:30 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:13:09 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"
#include "libft.h"

int		error(char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	return (0);
}

int		screenshot(t_scene *scene)
{
	int		width;
	int		height;
	int		*image;

	width = scene->window.width;
	height = scene->window.height;
	image = scene->window.img_data;
	if (!(image_to_bmp(height, width, image)))
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_scene		scene;

	if (argc != 2 && argc != 3)
		return (error("Usage: ./cub3D <.cub filepath> <-options>"));
	if (!(load_scene(argv[1], &scene)))
		return (0);
	ray_casting(&scene);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		screenshot(&scene);
		close_game(&scene);
		return (0);
	}
	render(&scene);
	mlx_hook((scene.window).win_ptr, 2, 0, press_key, &scene);
	mlx_hook((scene.window).win_ptr, 17, 0, close_game, &scene);
	mlx_loop((scene.window).mlx_ptr);
	return (0);
}
