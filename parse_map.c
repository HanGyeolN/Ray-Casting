#include "get_next_line.h"
#include "libft.h"
#include "libftprintf.h"
#include "raycasting.h"
#include <fcntl.h>

void	free_map(char **map, int map_h)
{
	while (++map_h < 10)
		free(map[map_h]);
	free(map);
}

char	**malloc_map(char **map, int fd, t_map *map_info)
{
	char	*line;
	int		map_w;
	int		map_h;

	map_w = 0;
	map_h = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > map_w)
			map_w = ft_strlen(line);
		map_h++;
	}
	map_info->width = map_w;
	map_info->height = map_h;
	if (!(map = malloc(sizeof(char *) * map_h)))
		return (0);
	while (map_h-- > 0)
	{
		if (!(map[map_h] = malloc(sizeof(char) * map_w)))
		{
			free_map(map, map_h);
			return (0);
		}
	}
	return (map);
}

char	**make_map(char *filename, t_map *map_info)
{
	int		i;
	int		fd;
	char	*line;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (!(map = malloc_map(map, fd, map_info)))
	{
		close(fd);
		return (0);
	}
	close(fd);
	i = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_strcpy(map[i], line);
		i++;
	}
	close(fd);
	return (map);
}