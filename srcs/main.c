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

int		main(void)
{
	t_scene		scene;
	t_cub		cub;

	if (!(load_scene("./test.cub", &scene, &cub)))
		return (0);
	ray_casting(&(scene.player.rays), &(scene.map), &scene);
	render(&scene);
	mlx_hook((scene.window).win_ptr, 2, 0, press_key, &scene);
	mlx_loop((scene.window).mlx_ptr);
}