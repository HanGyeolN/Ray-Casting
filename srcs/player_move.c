/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:18:49 by hna               #+#    #+#             */
/*   Updated: 2020/06/29 15:18:51 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		not_blocked(char c)
{
	if (c != '1' && c != '2')
		return (1);
	return (0);
}

void	move_front(t_map *map, t_player *p)
{
	char	target;
	double	speed;
	double	protect;

	protect = p->move_speed * 2;
	speed = p->move_speed;
	target = map->map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * protect)];
	if (not_blocked(target))
		p->pos_x += p->dir_x * speed;
	target = map->map[(int)(p->pos_y + p->dir_y * protect)][(int)p->pos_x];
	if (not_blocked(target))
		p->pos_y += p->dir_y * speed;
}

void	move_back(t_map *map, t_player *p)
{
	char	target;
	double	speed;

	speed = p->move_speed;
	target = map->map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)];
	if (not_blocked(target))
		p->pos_x -= p->dir_x * speed;
	target = map->map[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x];
	if (not_blocked(target))
		p->pos_y -= p->dir_y * speed;
}

void	move_right(t_map *map, t_player *p)
{
	double	dir_x;
	double	dir_y;
	double	theta;
	double	speed;

	theta = 90.0 * PI / 180;
	dir_x = p->dir_x * cos(theta) - p->dir_y * sin(theta);
	dir_y = p->dir_x * sin(theta) + p->dir_y * cos(theta);
	speed = p->move_speed;
	if (not_blocked(map->map[(int)p->pos_y][(int)(p->pos_x + dir_x * speed)]))
		p->pos_x += dir_x * speed;
	if (not_blocked(map->map[(int)(p->pos_y + dir_y * speed)][(int)p->pos_x]))
		p->pos_y += dir_y * speed;
}

void	move_left(t_map *map, t_player *p)
{
	double	dir_x;
	double	dir_y;
	double	theta;
	double	speed;

	theta = -90.0 * PI / 180;
	dir_x = p->dir_x * cos(theta) - p->dir_y * sin(theta);
	dir_y = p->dir_x * sin(theta) + p->dir_y * cos(theta);
	speed = p->move_speed;
	if (not_blocked(map->map[(int)p->pos_y][(int)(p->pos_x + dir_x * speed)]))
		p->pos_x += dir_x * speed;
	if (not_blocked(map->map[(int)(p->pos_y + dir_y * speed)][(int)p->pos_x]))
		p->pos_y += dir_y * speed;
}
