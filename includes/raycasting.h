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
# include <fcntl.h>

# define TEXTURE_SIZE 50

# define PI 3.14159265
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define N_RAY 800

# define WIDTH 800
# define HEIGHT 800
# define MAP_VIEW_W 500
# define MAP_VIEW_H 500

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
	double	rad;
	double	dydx;
	double	dist;
	int		color;
	int		side;
}					t_ray;

typedef struct		s_player
{
	double	pos_x;
	double	pos_y;
	double	rad;
	t_ray	rays[N_RAY];
}					t_player;

typedef struct		s_map
{
	double	width;
	double	height;
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
	int		(*n_data)[TEXTURE_SIZE];
	int		(*s_data)[TEXTURE_SIZE];
	int		(*w_data)[TEXTURE_SIZE];
	int		(*e_data)[TEXTURE_SIZE];
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

typedef struct		s_options
{
	int			res_w;
	int			res_h;
	char		*txr_no_path;
	char		*txr_so_path;
	char		*txr_we_path;
	char		*txr_ea_path;
	char		*txr_sp_path;
	int			f_color;
	int			c_color;
}					t_options;

int		is_ray_inf(t_ray *ray);
int		ray_casting(t_ray *ray, t_map *map, t_scene *scene);
int		put_map_to_img(t_map *map);
void	convert_3d(t_window *window, t_ray *ray, int i, char mode, t_scene *scene);
void	render(t_scene *scene);
char	**make_map(char *filename, t_map *map_info);
int		deal_key(int key, t_scene *scene);

#endif
