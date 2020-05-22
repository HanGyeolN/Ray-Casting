#include "raycasting.h"

void	move_front(t_map *map, t_player *p)
{
	double	speed;

	speed = p->move_speed;
	if (map->map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * speed)] != '1')
		p->pos_x += p->dir_x * speed;
	if (map->map[(int)(p->pos_y + p->dir_y * speed)][(int)p->pos_x] != '1')
		p->pos_y += p->dir_y * speed;
}

void	move_back(t_map *map, t_player *p)
{
	double	speed;

	speed = p->move_speed;
	if (map->map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * speed)] != '1')
		p->pos_x -= p->dir_x * speed;
	if (map->map[(int)(p->pos_y - p->dir_y * speed)][(int)p->pos_x] != '1')
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
	if (map->map[(int)p->pos_y][(int)(p->pos_x + dir_x * speed)] != '1')
		p->pos_x += dir_x * speed;
	if (map->map[(int)(p->pos_y + dir_y * speed)][(int)p->pos_x] != '1')
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
	if (map->map[(int)p->pos_y][(int)(p->pos_x + dir_x * speed)] != '1')
		p->pos_x += dir_x * speed;
	if (map->map[(int)(p->pos_y + dir_y * speed)][(int)p->pos_x] != '1')
		p->pos_y += dir_y * speed;
}