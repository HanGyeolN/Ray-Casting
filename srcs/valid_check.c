#include "raycasting.h"

int		check_texture(char *line, t_cub *cub, int *check)
{
	if (!(parse_path(line, cub, check)))
	{
		ft_printf("Texture Error\n");
		return (0);
	}
	return (1);
}

int		check_color(char *line, t_cub *cub, int *check)
{
	if (!(parse_color(line, cub, check)))
	{
		ft_printf("Floor Ceiling Error\n");
		return (0);
	}
	return (1);
}

int		check_resolution(char *line, t_cub *cub, int *check)
{
	if (!(parse_resolution(line, cub, check)))
	{
		ft_printf("Resolution Error\n");
		return (0);
	}
	if (cub->res_w > MAX_SC_W || cub->res_w < MIN_SC_W)
		cub->res_w = (cub->res_w < MIN_SC_W) ? MIN_SC_W : MAX_SC_W;
	if (cub->res_h > MAX_SC_H || cub->res_h < MIN_SC_H)
		cub->res_h = (cub->res_h < MIN_SC_H) ? MIN_SC_H : MAX_SC_H;
	return (1);
}

int		check_map(int fd, t_cub *cub, char *filepath)
{
	if (!(parse_map(fd, cub, filepath)))
		return (error("parse_map error"));
	convert_map(cub);
	if (!(is_valid_map(cub)))
		return (error("Not a valid map"));
	set_player(cub);
	return (1);
}