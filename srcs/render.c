/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:19:09 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:13:51 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	render(t_scene *scene)
{
	mlx_put_image_to_window((scene->window).mlx_ptr, \
							(scene->window).win_ptr, \
							(scene->window).img_ptr, \
							0, \
							0);
}
