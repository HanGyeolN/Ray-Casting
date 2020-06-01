#include "raycasting.h"

void	free_map(char **map, int map_h)
{
	while (++map_h < 10)
		free(map[map_h]);
	free(map);
}

void	set_map_size(t_cub *cub, int fd)
{
	char	*line;

	cub->map_w = 0;
	cub->map_h = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) == 0)
		{
			cub->line_n += 1;
			continue;
		}
		if (ft_strlen(line) > cub->map_w)
			cub->map_w = ft_strlen(line);
		(cub->map_h)++;
		free(line);
	}
	free(line);
	(cub->map_h)++;
}

char	**malloc_map(char **map, int fd, t_cub *cub)
{
	int		map_w;
	int		map_h;

	set_map_size(cub, fd);
	map_w = cub->map_w;
	map_h = cub->map_h;
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
		ft_memset(map[map_h], ' ', map_w);
		map[map_h][map_w] = '\0';
	}
	return (map);
}

char	**parse_map(int fd, t_cub *cub, char *filename)
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
	{
		get_next_line(fd, &line);
		free(line);
	}
	i = 0;
	while (get_next_line(fd, &line))
	{
		ft_strncpy(cub->map[i], line, ft_strlen(line));
		free(line);
		i++;
	}
	ft_strncpy(cub->map[i], line, ft_strlen(line));
	free(line);
	close(fd);
	return (cub->map);
}