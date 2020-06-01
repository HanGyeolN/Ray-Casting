#include "raycasting.h"

void	set_player_screen(t_scene *scene, int x)
{
	double		camera_x;
	t_window	*win;
	t_player	*p;

	win = &(scene->window);
	p = &(scene->player);
	camera_x = 2 * x / win->width - 1;
	p->rays[x].dir_x = p->dir_x + p->plane_x * camera_x;
	p->rays[x].dir_y = p->dir_y + p->plane_y * camera_x;
	p->rays[x].delta_dist_x = fabs(1 / p->rays[x].dir_x);
	p->rays[x].delta_dist_y = fabs(1 / p->rays[x].dir_y);
}

void	set_side_distance(t_scene *scene, int x)
{
	t_player	*p;
	t_ray		*r;

	p = &(scene->player);
	r = &(scene->player.rays[x]);
	if (r->dir_x < 0)
		r->side_dist_x = (p->pos_x - (int)p->pos_x) * r->delta_dist_x;
	else
		r->side_dist_x = ((int)p->pos_x + 1.0 - p->pos_x) * r->delta_dist_x;
	if (r->dir_y < 0)
		r->side_dist_y = (p->pos_y - (int)p->pos_y) * r->delta_dist_y;
	else
		r->side_dist_y = ((int)p->pos_y + 1.0 - p->pos_y) * r->delta_dist_y;
}

void	set_step_xy(t_scene *scene, int x)
{
	t_ray	*r;

	r = &(scene->player.rays[x]);
	if (r->dir_x < 0)
		r->step_x = -1;
	else
		r->step_x = 1;
	if (r->dir_y < 0)
		r->step_y = -1;
	else
		r->step_y = 1;
}

void	set_wall_perp_distance(t_player *p, t_ray *r, int map_x, int map_y)
{
	r->perp_wall_dist = (r->side == 0) ? \
			((map_x - p->pos_x + (1 - r->step_x) / 2) / r->dir_x) :
			((map_y - p->pos_y + (1 - r->step_y) / 2) / r->dir_y);
}

void	set_wall_distance(t_player *p, t_ray *r, t_map *map)
{
	int		map_x;
	int		map_y;
	int		hit;

	hit = 0;
	map_x = (int)p->pos_x;
	map_y = (int)p->pos_y;
	while (hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			map_y += r->step_y;
			r->side = 1;
		}
		if (map->map[map_y][map_x] == '1')
			hit = 1;
	}
	set_wall_perp_distance(p, r, map_x, map_y);
}

void	set_ray_distance(t_scene *scene, int x)
{
	t_ray	*r;

	r = &(scene->player.rays[x]);
	r->line_h = (int)(scene->window.height / (r->perp_wall_dist));
	r->draw_s = -(r->line_h) / 2 + scene->window.height / 2;
	if (r->draw_s < 0)
		r->draw_s = 0;
	r->draw_e = r->line_h / 2 + scene->window.height / 2;
	if (r->draw_e >= scene->window.height)
		r->draw_e = scene->window.height - 1;
	r->wall_x = (r->side == 0) ? \
		(scene->player.pos_y + r->perp_wall_dist * r->dir_y) :
		(scene->player.pos_x + r->perp_wall_dist * r->dir_x);
	r->wall_x -= floor(r->wall_x);	
}

void	set_ray_cardinal(t_scene *scene, int x)
{
	t_ray	*ray;

	ray = &(scene->player.rays[x]);
	if (ray->side == 1 && ray->dir_y >= 0)
		ray->cardinal = 0;
	else if (ray->side == 1 && ray->dir_y < 0)
		ray->cardinal = 2;
	else if (ray->side == 0 && ray->dir_x >= 0)
		ray->cardinal = 3;
	else if (ray->side == 0 && ray->dir_x < 0)
		ray->cardinal = 1;
}

int		get_color_by_cardinal(int cardinal, int x, int y, t_texture *t)
{
	int		color;

	color = 0;
	if (cardinal == 0)
		color = t->n_data[y][x];
	else if (cardinal == 1)
		color = t->e_data[y][x];
	else if (cardinal == 2)
		color = t->s_data[y][x];
	else if (cardinal == 3)
		color = t->w_data[y][x];
	return (color);
}

void	set_wall_texture(t_scene *scene, int x)
{
	int		y;
	int		tex_x;
	int		color;

	tex_x = (int)(scene->player.rays[x].wall_x * (double)TEXTURE_W);
	if (scene->player.rays[x].side == 0 && scene->player.rays[x].dir_x > 0)
		tex_x = TEXTURE_W - tex_x - 1;
	if (scene->player.rays[x].side == 1 && scene->player.rays[x].dir_y < 0)
		tex_x = TEXTURE_W - tex_x - 1;
	y = scene->player.rays[x].draw_s - 1;
	while (++y < scene->player.rays[x].draw_e)
	{
		int		tex_y;
		tex_y = y * 256 - (int)scene->window.height * 128 + scene->player.rays[x].line_h * 128;
		tex_y = ((tex_y * TEXTURE_H) / scene->player.rays[x].line_h) / 256;
		color = get_color_by_cardinal(scene->player.rays[x].cardinal, tex_x, tex_y, &scene->texture);
		if (scene->player.rays[x].side == 1)
			color = (color >> 1) & 8355711;
		scene->window.img_data[y * (int)scene->window.width + (x)] = color;
	}
}

void	set_fc_color(t_scene *scene, int x)
{
	int			y;
	t_window	*win;

	y = -1;
	win = &(scene->window);
	while (++y < scene->player.rays[x].draw_s)
		win->img_data[y * (int)win->width + x] = scene->c_color;
	y = scene->player.rays[x].draw_e - 1;
	while (++y < win->height)
		win->img_data[y * (int)win->width + x] = scene->f_color;
}

void	wall_casting(t_scene *scene)
{
	t_map	*map;
	int		x;

	map = &(scene->map);
	x = -1;
	while (++x < scene->window.width)
	{
		set_player_screen(scene, x);
		set_side_distance(scene, x);
		set_step_xy(scene, x);
		set_wall_distance(&(scene->player), &(scene->player.rays[x]), map);
		set_ray_cardinal(scene, x);
		set_ray_distance(scene, x);
		set_wall_texture(scene, x);
		set_fc_color(scene, x);
		scene->z_buffer[x] = scene->player.rays[x].perp_wall_dist;
	}
}