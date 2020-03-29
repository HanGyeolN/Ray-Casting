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

# define PI 3.14159265
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define N_RAY 150

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
	char	map[10][11];
}					t_map;

t_window	*window;
t_map		*map;
t_player	player;
void		*img_ptr1;
int			*img_data1;
void		*img_ptr2;
int			*img_data2;

void	render_ray(t_window *window, t_ray *ray, t_map *map);
int		render_map(t_window *window, t_map *map);
void	render_wall(t_window *window, t_ray *ray, int i, char mode);
void	render(void);

#endif
