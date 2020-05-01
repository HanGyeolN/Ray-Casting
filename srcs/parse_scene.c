#include "raycasting.h"
#include "libftprintf.h"

/*
** Calculate number of splited word 
*/

int		split_len(char **splits)
{
	int		len;

	len = 0;
	while (splits[len])
		len++;
	return (len);
}

/*
** free after ft_split function
*/

void	free_splits(char **splits)
{
	int		i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

/*
** parsing if ft_strncmp(line, "R ", 2) is 0.
** use line string, put data into cub structure
*/

int		parse_resolution(char *line, t_cub *cub, int *check)
{
	char	**splits;
	int		i;
	int		idx;
	int		len;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 3)
		return (0);
	idx = 1;
	while (idx < 3)
	{
		i = -1;
		len = ft_strlen(splits[idx]);
		while (++i < len)
			if (is_numeric(splits[idx][i]) == 0)
				return (0);
		if (idx == 1)
			cub->res_w = ft_atoi(splits[idx]);
		else
			cub->res_h = ft_atoi(splits[idx]);
		idx++;
	}
	*check += 0b10000000;
	free_splits(splits);
	return (1);
}

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

int		parse_path(char *line, t_cub *cub, int *check)
{
	char	**splits;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 2)
		return (0);
	if (ft_strcmp(splits[0], "NO") == 0)
	{
		ft_strcpy(cub->tex_n, splits[1]);
		*check += 0b01000000;
	}
	else if (ft_strcmp(splits[0], "SO") == 0)
	{
		ft_strcpy(cub->tex_s, splits[1]);
		*check += 0b00100000;
	}
	else if (ft_strcmp(splits[0], "WE") == 0)
	{
		ft_strcpy(cub->tex_w, splits[1]);
		*check += 0b00010000;
	}
	else if (ft_strcmp(splits[0], "EA") == 0)
	{
		ft_strcpy(cub->tex_e, splits[1]);
		*check += 0b00001000;
	}
	else if (ft_strcmp(splits[0], "S") == 0)
	{
		ft_strcpy(cub->tex_i, splits[1]);
		*check += 0b00000100;
	}
	free_splits(splits);
	return (1);
}

/*
** check color
** valid color range : 0 to 255
*/

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

/*
** parsing color integer
*/

int		parse_color(char *line, t_cub *cub, int *check)
{
	char	**splits;
	char	**colors;
	int		color;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 2)
		return (0);
	colors = ft_split(splits[1], ',');
	if (split_len(colors) != 3 || !(is_valid_color(colors)))
		return (0);
	color = 0;
	color += 16 * 16 * 16 * 16 * ft_atoi(colors[0]);
	color += 16 * 16 * ft_atoi(colors[1]);
	color += ft_atoi(colors[2]);
	if (splits[0][0] == 'F')
	{
		cub->color_f = color;
		*check += 0b00000010;
	}
	else if (splits[0][0] == 'C')
	{
		cub->color_c = color;
		*check += 0b00000001;
	}
	free_splits(splits);
	free_splits(colors);
	return (1);
}

/*
** check keyword from .cub file
** texture keyword : NO, SO, WE, EA, S
*/

void	free_map(char **map, int map_h)
{
	while (++map_h < 10)
		free(map[map_h]);
	free(map);
}

char	**malloc_map(char **map, int fd, t_cub *cub)
{
	char	*line;
	int		map_w;
	int		map_h;

	map_w = 0;
	map_h = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) == 0)
		{
			cub->line_n += 1;
			continue;
		}
		if (ft_strlen(line) > map_w)
			map_w = ft_strlen(line);
		map_h++;
	}
	cub->map_w = map_w;
	cub->map_h = map_h;
	if (!(map = malloc(sizeof(char *) * (map_h + 1))))
		return (0);
	map[map_h] = 0;
	while (map_h-- > 0)
	{
		if (!(map[map_h] = malloc(sizeof(char) * (map_w + 1))))
		{
			free_map(map, map_h);
			return (0);
		}
		map[map_h][map_w] = '\0';
	}
	return (map);
}

char	**make_map(int fd, t_cub *cub, char *filename)
{
	int		i;
	char	*line;

	if (!(cub->map = malloc_map(cub->map, fd, cub)))
	{
		close(fd);
		return (0);
	}
	close(fd);
	i = -1;
	fd = open(filename, O_RDONLY);
	while (++i < cub->line_n)
		get_next_line(fd, &line);
	i = 0;
	while (get_next_line(fd, &line))
	{
		ft_strlcpy(cub->map[i], line, (cub->map_w + 1));
		i++;
	}
	close(fd);
	return (cub->map);
}

int		is_sprite(char n)
{
	if (n == '2')
		return (1);
	return (0);
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
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' ||
				cub->map[y][x] == 'W' || cub->map[y][x] == 'E')
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
				chk++;
			}
		}
	}
	if (chk == 1)
		return (1);
	ft_printf("player initial position error\n");
	return (0);
}

int		is_resolution(char *line)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (1);
	return (0);
}

int		is_texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 ||
			ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 ||
			ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "S ", 2) == 0)
		return (1);
	return (0);
}

int		is_floor_ceiling(char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int		check_resolution(char *line, t_cub *cub, int *check)
{
	if (!(parse_resolution(line, cub, check)))
	{
		ft_printf("Resolution Error\n");
		return (0);
	}
	return (1);
}

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

int		check_map(int fd, t_cub *cub, char *filepath)
{
	if (!(make_map(fd, cub, filepath)) || !(set_player(cub)))
	{
		ft_printf("map error\n");
		return (0);
	}
	return (1);
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