#include "raycasting.h"

/*
** parsing color integer
*/

int		get_color(char **colors)
{
	int		color;

	color = 0;
	color += 16 * 16 * 16 * 16 * ft_atoi(colors[0]);
	color += 16 * 16 * ft_atoi(colors[1]);
	color += ft_atoi(colors[2]);
	return (color);
}

int		parse_color(char *line, t_cub *cub, int *check)
{
	char	**splits;
	char	**colors;
	int		color;

	splits = ft_split(line, ' ');
	if (split_len(splits) != 2)
		return (error("color parsing error | split length is not 2."));
	colors = ft_split(splits[1], ',');
	if (split_len(colors) != 3 || !(is_valid_color(colors)))
		return (error("color parsing error"));
	color = get_color(colors);
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