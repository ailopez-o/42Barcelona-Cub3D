/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:35:30 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/05 10:46:25 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		validate_map(char *path, t_cub *cub);

bool	parse_map(int argv, char **argc, t_cub *cub)
{
	if (argv != 2)
		return (EXIT_FAILURE);
	if (ft_strlen(argc[1]) < 4 || ft_strncmp(argc[1] + (ft_strlen(argc[1]) - 4),
			".cub", 5))
		return (EXIT_FAILURE);
	if (validate_map(argc[1], cub))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_player(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == 'N')
			return (pos);
		if (line[pos] == 'S')
			return (pos);
		if (line[pos] == 'E')
			return (pos);
		if (line[pos] == 'W')
			return (pos);
		pos++;
	}
	return (0);
}

bool	square_map(char **map, int max_x)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		map[i] = ft_realloc(map[i], max_x + 1);
		j = len;
		while (j < max_x)
		{
			map[i][j] = '0';
			j++;
		}
		map[i][max_x] = '\0';
		i++;
	}
	return (true);
}

bool	line_has_wall(char *line)
{
	bool	has_wall;

	has_wall = false;
	if (*line == ' ' || *line == '0' || *line == '1')
	{
		while (*line)
		{
			if (*line == '1')
				has_wall = true;
			line++;
		}
	}
	return (has_wall);
}
