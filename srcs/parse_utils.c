#include "raycasting.h"

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