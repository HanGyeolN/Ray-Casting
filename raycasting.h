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

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef struct	s_window
{
	double	width;
	double	height;
	void	*win_ptr;
	void	*mlx_ptr;
}				t_window;

typedef struct	s_ray
{
	double	pos_x;
	double	pos_y;
	double	rad;
	double	dydx;
	int		color;
	int		hit;
	double	hit_x;
	double	hit_y;
}				t_ray;

typedef struct		s_map
{
	double	width;
	double	height;
	int		block_w;
	int		block_h;
	int		color;
	char	map[10][11];
}					t_map;

void	render_ray(t_window *window, t_ray *ray, t_map *map);
int		render_map(t_window *window, t_map *map);

#endif
