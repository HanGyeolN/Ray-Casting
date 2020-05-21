#include "raycasting.h"

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