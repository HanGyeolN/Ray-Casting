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
#include "libft.h"

int		error(char *error_msg)
{
	ft_printf("Error\n");
	ft_printf("%s\n", error_msg);
	return (0);
}

int		main(int argc, char **argv)
{
	t_scene		scene;
	t_cub		cub;

	if (argc != 2 && argc != 3)
		return (error("Usage: ./cub3D <.cub filepath>"));
	if (!(load_scene(argv[1], &scene, &cub)))
		return (error(".cub misconfiguration"));
	ray_casting(&(scene.map), &scene);
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		screen_shot(scene.window.height, scene.window.width, scene.window.img_data);
		close_game(&scene);
		return (0);
	}
	render(&scene);
	mlx_hook((scene.window).win_ptr, 2, 0, press_key, &scene);
	mlx_hook((scene.window).win_ptr, 17, 0, close_game, &scene);
	mlx_loop((scene.window).mlx_ptr);
}