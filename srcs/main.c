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

void	casting(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < (int)(scene->window).width)
	{
		ray_casting(&(scene->player.rays), &(scene->map), scene);
		i++;
	}
}

void	convert(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < (int)(scene->window).width)
	{
		convert_3d(&(scene->window), &(scene->player.rays[i]), i, 'a', scene);
		i++;
	}
}

int		main(void)
{
	t_scene		scene;
	t_cub		cub;

	if (!(load_scene("./test.cub", &scene, &cub)))
		return (0);
	ray_casting(&(scene.player.rays), &(scene.map), &scene);
//	casting(&scene);
//	convert(&scene);
	render(&scene);
	// mlx_hook((scene.window).win_ptr, 2, 0, press_key, &scene);
	// mlx_hook((scene.window).win_ptr, 3, 0, release_key, &scene);
	mlx_hook((scene.window).win_ptr, 2, 0, press_key, &scene);
//	mlx_key_hook((scene.window).win_ptr, press_key, &scene);
	mlx_loop((scene.window).mlx_ptr);
}