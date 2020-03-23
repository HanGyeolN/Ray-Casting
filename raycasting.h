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
}				t_ray;

typedef struct		s_map
{
	double	width;
	double	height;
	char	map[5][7];
}					t_map;

void	render_ray(t_window *window, t_ray *ray);
int		render_map(t_window *window, t_map *map);

#endif
