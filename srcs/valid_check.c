/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:19:31 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 19:05:30 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

int		check_texture(char *line, t_cub *cub, int *check)
{
	if (!(parse_path(line, cub, check)))
		return (0);
	return (1);
}

int		check_color(char *line, t_cub *cub, int *check)
{
	if (!(parse_color(line, cub, check)))
		return (0);
	return (1);
}

void	adjust_resolution(t_cub *cub)
{
	if (cub->res_w > MAX_SC_W || cub->res_w < MIN_SC_W)
		cub->res_w = (cub->res_w < MIN_SC_W) ? MIN_SC_W : MAX_SC_W;
	if (cub->res_h > MAX_SC_H || cub->res_h < MIN_SC_H)
		cub->res_h = (cub->res_h < MIN_SC_H) ? MIN_SC_H : MAX_SC_H;
}

int		check_resolution(char *line, t_cub *cub, int *check)
{
	if (!(parse_resolution(line, cub, check)))
		return (0);
	adjust_resolution(cub);
	return (1);
}

int		check_map(int fd, t_cub *cub, char *filepath)
{
	if (!(parse_map(fd, cub, filepath)))
		return (error("parse_map error"));
	if (!(is_valid_map(cub)))
		return (0);
	convert_map(cub);
	if (!(set_player(cub)))
		return (error("player position error"));
	return (1);
}
