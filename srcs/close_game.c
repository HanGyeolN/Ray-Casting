/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 16:02:54 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 20:30:27 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		close_game(t_scene *scene)
{
	int		i;

	free(scene->z_buffer);
	free(scene->sprite);
	free(scene->player.rays);
	i = -1;
	while (++i < scene->map.height + 1)
		free(scene->map.map[i]);
	free(scene->map.map);
	mlx_destroy_image(scene->window.mlx_ptr, scene->window.img_ptr);
	mlx_destroy_window(scene->window.mlx_ptr, scene->window.win_ptr);
	exit(0);
}
