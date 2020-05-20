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
# define SPRITE_W 25
# define SPRITE_H 25

# define PI 3.14159265
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

# define SPEED_MOVE 1
# define SPEED_ROT 2

# define MAX_SC_W 1920
# define MIN_SC_W 400
# define MAX_SC_H 1080
# define MIN_SC_H 280


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
	double	hit_x;
	double	hit_y;
	double	dir_x;
	double	dir_y;
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
	int		cardinal;
	int		hit;
	char	hit_type;
}					t_ray;

typedef struct		s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double	rad;
	t_ray	*rays;
}					t_player;

typedef struct		s_map
{
	double	width;
	double	height;
	int		width_r;
	int		height_r;
	int		block_w;
	int		block_h;
	int		color;
	char	**map;
	void	*image;
	int		*data;
}					t_map;

typedef struct		s_texture
{
	void	*n;
	void	*s;
	void	*w;
	void	*e;
	void	*f;
	void	*c;
	void	*i;
	int		(*n_data)[TEXTURE_SIZE];
	int		(*s_data)[TEXTURE_SIZE];
	int		(*w_data)[TEXTURE_SIZE];
	int		(*e_data)[TEXTURE_SIZE];
	int		(*f_data)[TEXTURE_SIZE];
	int		(*c_data)[TEXTURE_SIZE];
	int		(*i_data)[SPRITE_W];
}					t_texture;

typedef struct		s_sprite
{
	double	x;
	double	y;
	int		d;
	char	type;
}					t_sprite;

typedef struct		s_scene
{
	t_window	window;
	t_map		map;
	t_texture	texture;
	t_player	player;
	t_sprite	*sprite;
	int			f_color;
	int			c_color;
	int			n_sprite;
	double		*z_buffer;
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
	int		n_sprite;
	int		sprite_x[200];
	int		sprite_y[200];
}				t_cub;

typedef struct	s_bitmap_file_header
{
	unsigned char	bf_type[2];
	unsigned char	bf_size[4];
	short			bf_reserved1;
	short			bf_reserved2;
	unsigned char	bf_off_bits[4];
}				t_bitmap_file_header;

typedef struct	s_bitmap_info_header
{
	unsigned char	bi_size[4];
	unsigned char	bi_width[4];
	unsigned char	bi_height[4];
	unsigned char	bi_planes[2];
	unsigned char	bi_bit_count[2];
	int		bi_compression;
	int		bi_size_image;
	int		bi_xpels_per_meter;
	int		bi_ypels_per_meter;
	int		bi_clr_used;
	int		bi_clr_important;
}				t_bitmap_info_header;

typedef struct	s_bitmap
{
	t_bitmap_file_header	file_header;
	t_bitmap_info_header	info_header;
	unsigned char			*image;
}				t_bitmap;


int		sprite_order[100];
double	sprite_distance[100];

int		ray_casting(t_map *map, t_scene *scene);
void	render(t_scene *scene);
char	**make_map(int fd, t_cub *cub, char *filename);
int		parse_scene(char *filepath, t_cub *cub);
int		press_key(int key, t_scene *scene);
int		release_key(int key, t_scene *scene);
int		load_scene(char *scene_path, t_scene *scene, t_cub *cub);
int		screen_shot(int height, int width, int *img_data);
int		error(char *error_msg);
int		close_game(t_scene *scene);

void	move_front(t_map *map, t_player *p);
void	move_back(t_map *map, t_player *p);
void	move_right(t_map *map, t_player *p);
void	move_left(t_map *map, t_player *p);
void	rotate_right(t_player *p);
void	rotate_left(t_player *p);

#endif
