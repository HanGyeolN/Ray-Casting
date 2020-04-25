/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 04:04:51 by hna               #+#    #+#             */
/*   Updated: 2020/03/23 04:37:14 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAYCASTING_H
# define RAYCASTING_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "libftprintf.h"
# include <fcntl.h>

# define TEXTURE_SIZE 50
# define TEXTURE_H 50
# define TEXTURE_W 50

# define PI 3.14159265
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124

# define SPEED_MOVE 1
# define SPEED_ROT 2

typedef struct		s_window
{
	double	width;
	double	height;
	void	*win_ptr;
	void	*mlx_ptr;
	void	*img_ptr;
	int		*img_data;
}					t_window;

typedef struct		s_ray
{
	double	pos_x;
	double	pos_y;
	double	hit_x;
	double	hit_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	rad;
	double	dist;
	double	wall_x;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		color;
	int		side;
	int		hit;
	char	hit_type;
}					t_ray;

typedef struct		s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
	double	rad;
	t_ray	*rays;
}					t_player;

typedef struct		s_map
{
	double	width;
	double	height;
	double	width_r;
	double	height_r;
	int		block_w;
	int		block_h;
	int		color;
	char	**map;
	char	**map_r;
	void	*image;
	int		*data;
}					t_map;

typedef struct		s_texture
{
	void	*n;
	void	*s;
	void	*w;
	void	*e;
	void	*i;
	int		(*n_data)[TEXTURE_SIZE];
	int		(*s_data)[TEXTURE_SIZE];
	int		(*w_data)[TEXTURE_SIZE];
	int		(*e_data)[TEXTURE_SIZE];
	int		(*i_data)[TEXTURE_SIZE];
}					t_texture;

typedef struct		s_scene
{
	t_window	window;
	t_map		map;
	t_texture	texture;
	t_player	player;
	int			floor_color;
	int			ceilling_color;
}					t_scene;

/*
** Maximum path length : 200
*/

typedef struct	s_cub
{
	int		line_n;
	int		res_w;
	int		res_h;
	char	tex_n[200];
	char	tex_s[200];
	char	tex_w[200];
	char	tex_e[200];
	char	tex_i[200];
	int		color_f;
	int		color_c;
	char	**map;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	double	player_dir;
}				t_cub;

int		is_ray_inf(t_ray *ray);
int		ray_casting(t_ray **rays, t_map *map, t_scene *scene);
int		put_map_to_img(t_map *map);
void	convert_3d(t_window *window, t_ray *ray, int i, char mode, t_scene *scene);
void	render(t_scene *scene);
char	**make_map(int fd, t_cub *cub, char *filename);
int		parse_scene(char *filepath, t_cub *cub);
int		deal_key(int key, t_scene *scene);
int		load_scene(char *scene_path, t_scene *scene, t_cub *cub);

#endif
