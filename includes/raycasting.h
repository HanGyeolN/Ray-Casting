/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 04:04:51 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 20:21:53 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
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
# define SPRITE_W 50
# define SPRITE_H 50

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

# define BYTES_PER_PIXEL 3
# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

typedef struct	s_window
{
	double	width;
	double	height;
	void	*win_ptr;
	void	*mlx_ptr;
	void	*img_ptr;
	int		*img_data;
}				t_window;

typedef struct	s_floor
{
	float	row_dist;
	float	f_stepx;
	float	f_stepy;
	float	floor_x;
	float	floor_y;
}				t_floor;

typedef struct	s_ray
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
	double	dist;
	double	wall_x;
	int		step_x;
	int		step_y;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		color;
	int		side;
	int		cardinal;
}				t_ray;

typedef struct	s_player
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
}				t_player;

typedef struct	s_map
{
	double	width;
	double	height;
	int		block_w;
	int		block_h;
	int		color;
	char	**map;
	void	*image;
	int		*data;
}				t_map;

typedef struct	s_texture
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
}				t_texture;

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		d;
	char	type;
}				t_sprite;

typedef struct	s_spritev
{
	int		scale_w;
	int		scale_h;
	int		color;
	int		v_move_screen;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	trans_x;
	double	trans_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	int		tex_y;
}				t_spritev;

typedef struct	s_scene
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
}				t_scene;

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

typedef struct	s_bmp_fh
{
	unsigned char	bf_type[2];
	unsigned char	bf_size[4];
	short			bf_reserved1;
	short			bf_reserved2;
	unsigned char	bf_off_bits[4];
}				t_bmp_fh;

typedef struct	s_bmp_ih
{
	unsigned char	bi_size[4];
	unsigned char	bi_width[4];
	unsigned char	bi_height[4];
	unsigned char	bi_planes[2];
	unsigned char	bi_bit_count[2];
	int				bi_compression;
	int				bi_size_image;
	int				bi_xpels_per_meter;
	int				bi_ypels_per_meter;
	int				bi_clr_used;
	int				bi_clr_important;
}				t_bmp_ih;

/*
** Initialize
*/

int				init_sprite(t_map *map, t_scene *scene);
int				init_player(t_player *player, t_cub *cub);
int				init_texture(void *mlx_ptr, t_texture *t, t_cub *cub);
void			init_map(t_map *map, t_cub *cub);
void			init_mlx_window(t_scene *scene, \
								t_cub *cub, \
								char *title);

/*
** Parsing Utils
*/

int				is_resolution(char *line);
int				is_texture(char *line);
int				is_floor_ceiling(char *line);
void			free_splits(char **splits);
int				split_len(char **splits);

/*
** Parsing
*/

int				load_scene(char *scene_path, t_scene *scene);
int				convert_map(t_cub *cub);
int				set_player(t_cub *cub);
char			**parse_map(int fd, t_cub *cub, char *filename);
int				parse_scene(char *filepath, t_cub *cub);
int				parse_color(char *line, t_cub *cub, int *check);
int				parse_resolution(char *line, t_cub *cub, int *check);
int				parse_path(char *line, t_cub *cub, int *check);

/*
** Validation Check
*/

int				is_valid_map(t_cub *cub);
int				is_valid_color(char **colors);
int				check_color(char *line, t_cub *cub, int *check);
int				check_texture(char *line, t_cub *cub, int *check);
int				check_map(int fd, t_cub *cub, char *filepath);
int				check_resolution(char *line, t_cub *cub, int *check);
int				is_closed(t_cub *cub);

/*
** Event
*/

int				press_key(int key, t_scene *scene);
int				close_game(t_scene *scene);
void			move_front(t_map *map, t_player *p);
void			move_back(t_map *map, t_player *p);
void			move_right(t_map *map, t_player *p);
void			move_left(t_map *map, t_player *p);
void			rotate_right(t_player *p);
void			rotate_left(t_player *p);
void			rotate_player(t_player *p, double spd);
void			rotate_plane(t_player *p, double spd);

/*
** Raycasting
*/

void			set_wall_texture(t_scene *scene, int x);
void			set_wall_perp_distance(t_player *p, \
										t_ray *r, \
										int map_x, \
										int map_y);
void			set_player_screen(t_scene *scene, int x);
void			set_side_distance(t_scene *scene, int x);
void			set_step_xy(t_scene *scene, int x);
void			wall_casting(t_scene *scene);
void			floor_casting(t_scene *scene);
void			sprite_casting(t_scene *scene);
int				ray_casting(t_scene *scene);

/*
** Sprite Utils
*/

int				*get_sprite_order(t_scene *scene);
void			sort_sprites(int *order, double *dist, int amount);
int				image_to_bmp(int height, int width, int *img_data);
int				error(char *error_msg);
void			render(t_scene *scene);

#endif
