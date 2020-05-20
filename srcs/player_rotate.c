#include "raycasting.h"

void	rotate_player(t_player *p, double spd)
{
	double old_dir_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(spd) - p->dir_y * sin(spd);
	p->dir_y = old_dir_x * sin(spd) + p->dir_y * cos(spd);
}

void	rotate_plane(t_player *p, double spd)
{
	double old_plane_x;

	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(spd) - p->plane_y * sin(spd);
	p->plane_y = old_plane_x * sin(spd) + p->plane_y * cos(spd);
}

void	rotate_right(t_player *p)
{
	rotate_player(p, p->rot_speed);
	rotate_plane(p, p->rot_speed);
}

void	rotate_left(t_player *p)
{
	rotate_player(p, -(p->rot_speed));
	rotate_plane(p, -(p->rot_speed));
}