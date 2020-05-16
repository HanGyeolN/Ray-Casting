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

int		close_game(t_scene *scene)
{
	int		i;
	ft_printf("Red cross button pushed\n");
	free(scene->z_buffer);
	free(scene->sprite);
	free(scene->player.rays);
	i = 0;
	while (i < scene->map.height)
	{
		free(scene->map.map_r[i]);
		i++;
	}
	free(scene->map.map_r);
	mlx_destroy_image(scene->window.mlx_ptr, scene->window.img_ptr);
	mlx_destroy_window(scene->window.mlx_ptr, scene->window.win_ptr);
	exit (0);
}

int		main(int argc, char **argv)
{
	t_scene		scene;
	t_cub		cub;

	if (!(load_scene("./test.cub", &scene, &cub)))
		return (0);
	ray_casting(&(scene.player.rays), &(scene.map), &scene);
	if (argc == 2 && ft_strcmp(argv[1], "--save") == 0)
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