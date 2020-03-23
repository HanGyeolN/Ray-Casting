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
# include "mlx.h"

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
	double	deg_x;
	double	deg_y;
	double	rad;
}				t_ray;

#endif
