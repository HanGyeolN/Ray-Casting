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
# include "mlx.h"

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
# define HEIGHT 600
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
	double	gw;
	double	gh;
}					t_window;

typedef struct		s_ray
{
	int		pos_x;
	int		pos_y;
	double	rad;
	double	dydx;
	int		color;
	double	hit_x;
	double	hit_y;
	double	dist;
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
}					t_map;

typedef struct		s_texture
{
	void	*n;
	void	*s;
	void	*w;
	void	*e;
	int		*n_data;
	int		*s_data;
	int		*w_data;
	int		*e_data;
}					t_texture;

t_window	*window;
t_map		*map;
t_player	player;
void		*img_ptr1;
int			*img_data1;
void		*img_ptr2;
int			*img_data2;
void		*tx_img;
int			(*tx_data)[TEXTURE_SIZE];

int		is_ray_inf(t_ray *ray);
void	render_ray(t_window *window, t_ray *ray, t_map *map);
int		render_map(t_window *window, t_map *map);
void	render_wall(t_window *window, t_ray *ray, int i, char mode);
void	render(void);
char	**make_map(char *filename, t_map *map_info);

#endif
