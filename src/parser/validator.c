/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:02:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/07/19 19:10:01 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	parse_map(int argv, char **argc,char **map)
{
	if (argc != 2)
		return EXIT_FAILURE;
	if (ft_strlen(argv[1]) < 4
		|| ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 4), ".cub", 5))
		return EXIT_FAILURE;
	if (!validate_map(argv[1]))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

bool	validate_map(char *path)
{

	return valid_map_from_player(map);
}

bool	valid_map_from_player(int x, int y, char map[11][8],char checker[11][8], int max_height, int max_width)
{
	int its = 0;

	if (checker[y][x] == '1')
		return 0;
	checker[y][x] = '1';
	if (map[y][x] == '1')
		return 0;
	if (x > 0)
		its += valid_map_from_player(x - 1, y, map, checker);
	if (x < max_width)
		its += valid_map_from_player(x + 1, y, map, checker);
	if (y > 0)
		its += valid_map_from_player(x, y - 1, map, checker);
	if (y < max_height)
		its += valid_map_from_player(x, y + 1, map, checker);
	if ((x == 0 || x == max_width) && map[y][x] == '0')
		return 1;
	if ((y == 0 || y == max_height) && map[y][x] == '0')
		return 1;
	if (its)
		return 1;
	return 0;
}