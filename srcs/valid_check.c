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
	convert_map(cub);
	if (!(is_valid_map(cub)))
		return (0);
	if (!(set_player(cub)))
		return (error("player position error"));
	return (1);
}

int		is_valid_color(char **colors)
{
	int		idx;
	int		i;
	idx = 0;
	i = -1;
	while (idx < 3)
	{
		while (++i < ft_strlen(colors[idx]))
			if (is_numeric(colors[idx][i]) == 0)
				return (0);
		if (ft_atoi(colors[idx]) < 0 || ft_atoi(colors[idx]) > 255)
			return (0);
		idx++;
	}
	return (1);
}