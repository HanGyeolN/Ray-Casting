#include "raycasting.h"

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
		return (error("resolution parsing error | split length is not 3"));
	idx = 1;
	while (idx < 3)
	{
		i = -1;
		len = ft_strlen(splits[idx]);
		while (++i < len)
			if (is_numeric(splits[idx][i]) == 0)
				return (error("resolution parsing error | not a number"));
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

int		parse_path(char *line, t_cub *cub, int *check)
{
	char	**spts;

	spts = ft_split(line, ' ');
	if (split_len(spts) != 2)
	{
		free_splits(spts);
		return (error("texture path parsing error | split len is not 2"));
	}
	if (ft_strcmp(spts[0], "NO") == 0 && ft_strcpy(cub->tex_n, spts[1]))
		*check += 0b01000000;
	else if (ft_strcmp(spts[0], "SO") == 0 && ft_strcpy(cub->tex_s, spts[1]))
		*check += 0b00100000;
	else if (ft_strcmp(spts[0], "WE") == 0 && ft_strcpy(cub->tex_w, spts[1]))
		*check += 0b00010000;
	else if (ft_strcmp(spts[0], "EA") == 0 && ft_strcpy(cub->tex_e, spts[1]))
		*check += 0b00001000;
	else if (ft_strcmp(spts[0], "S") == 0 && ft_strcpy(cub->tex_i, spts[1]))
		*check += 0b00000100;
	free_splits(spts);
	return (1);
}