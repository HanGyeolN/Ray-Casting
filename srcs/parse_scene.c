#include "raycasting.h"
#include "libftprintf.h"

void	print_cub(t_cub *cub)
{
	int		i;

	i = 0;
	ft_printf("Resolution Width: %d\n", cub->res_w);
	ft_printf("Resolution Height: %d\n", cub->res_h);
	ft_printf("Texture North: %s\n", cub->tex_n);
	ft_printf("Texture South: %s\n", cub->tex_s);
	ft_printf("Texture West: %s\n", cub->tex_w);
	ft_printf("Texture East: %s\n", cub->tex_e);
	ft_printf("Texture Item: %s\n", cub->tex_i);
	ft_printf("Floor Color: %x\n", cub->color_f);
	ft_printf("Ceiling Color: %x\n", cub->color_c);
	ft_printf("Map Width: %d\n", cub->map_w);
	ft_printf("Map Height: %d\n", cub->map_h);
	ft_printf("============map============\n");
	while (i < cub->map_h)
	{
		ft_printf("%s\n", (cub->map)[i]);
		i++;
	}
	ft_printf("===========================\n");
	ft_printf("Player Position X: %d\n", cub->player_x);
	ft_printf("Player Position Y: %d\n", cub->player_y);
	ft_printf("Player Direction: %d\n", (int)cub->player_dir);
}

/*
** check keyword from .cub file
** texture keyword : NO, SO, WE, EA, S
*/

void	set_player_direction(t_cub *cub, int y, int x)
{
	if (cub->map[y][x] == 'N')
		cub->player_dir = 270.0;
	else if (cub->map[y][x] == 'S')
		cub->player_dir = 90.0;
	else if (cub->map[y][x] == 'W')
		cub->player_dir = 180.0;
	else
		cub->player_dir = 0.0;
	cub->player_x = x;
	cub->player_y = y;
}

int		set_player(t_cub *cub)
{
	int		x;
	int		y;
	int		chk;

	chk = 0;
	y = -1;
	while (++y < cub->map_h)
	{
		x = -1;
		while (++x < cub->map_w)
		{
			if (ft_strchr("NSWE", cub->map[y][x]))
			{
				set_player_direction(cub, y, x);
				chk++;
			}
		}
	}
	if (chk == 1)
		return (1);
	return (0);
}

void	convert_space(t_cub *cub, int r, int c)
{
	int		t;
	int		check;

	t = 1;
	check = 0;
	if (cub->map[r][c] == ' ')
	{
		while (c + t < cub->map_w && c - t >= 0)
		{
			if ((cub->map[r][c + t] != '1' && cub->map[r][c + t] != ' ') || (cub->map[r][c - t] != '1' && cub->map[r][c - t] != ' '))
			{
				cub->map[r][c] = '0';
				check = 1;
				break;
			}
			t++;
		}
		if (check == 0)
			cub->map[r][c] = '1';
	}
}

int		convert_map(t_cub *cub)
{
	int		r;
	int		c;

	r = -1;
	while (++r < cub->map_h)
	{
		c = -1;
		while (++c < cub->map_w)
			convert_space(cub, r, c);
	}
	return (0);
}

int		parse_scene(char *filepath, t_cub *cub)
{
	int		fd;
	int		check;
	char	*line;

	check = 0b00000000;
	cub->line_n = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		perror("[scene open]");
	while (get_next_line(fd, &line) > 0)
	{
		cub->line_n += 1;
		if (is_resolution(line) && !(check_resolution(line, cub, &check)))
			return (0);
		else if (is_texture(line) && !(check_texture(line, cub, &check)))
			return (0);
		else if (is_floor_ceiling(line) && !(check_color(line, cub, &check)))
			return (0);
		if (check == 0b11111111 && !(check_map(fd, cub, filepath)))
			return (0);
	}
	close(fd);
	print_cub(cub);
	return (1);
}