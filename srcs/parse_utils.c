/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 15:18:38 by hna               #+#    #+#             */
/*   Updated: 2020/07/01 16:17:31 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(splits[i]);
	free(splits);
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
