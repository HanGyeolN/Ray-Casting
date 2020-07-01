/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:19:24 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:26:17 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	sort_sprites(int *order, double *dist, int amount)
{
	int		i;
	int		j;
	int		temp;
	double	tp;

	i = -1;
	while (++i < amount)
	{
		j = i;
		while (++j < amount)
		{
			if (dist[i] < dist[j])
			{
				temp = order[i];
				order[i] = order[j];
				order[j] = temp;
				tp = dist[i];
				dist[i] = dist[j];
				dist[j] = tp;
			}
		}
	}
}

int		*get_sprite_order(t_scene *scene)
{
	int		i;
	int		*sprite_order;
	int		n_sprite;
	double	*sprite_distance;

	n_sprite = scene->n_sprite;
	i = 0;
	if (!(sprite_order = malloc(sizeof(int) * n_sprite)))
		return (0);
	if (!(sprite_distance = malloc(sizeof(double) * n_sprite)))
		return (0);
	while (i < n_sprite)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (scene->player.pos_x - scene->sprite[i].x) * \
							(scene->player.pos_x - scene->sprite[i].x);
		sprite_distance[i] += (scene->player.pos_y - scene->sprite[i].y) * \
							(scene->player.pos_y - scene->sprite[i].y);
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, n_sprite);
	free(sprite_distance);
	return (sprite_order);
}
