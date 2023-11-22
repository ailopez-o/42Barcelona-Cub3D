/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:47:05 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 11:57:05 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

int			**empty_map(int width, int height);
bool		validate_map(char *path, t_cub *cub);
bool		valid_map_from_player(int x, int y, char **map, int max_x,
				int max_y);
char		*get_int_array(char *line);
int			get_data_type(char *line);
int			add_texture(char *path, t_texture *textures, t_mlx *screen,
				int type);
int			color_parser(char *line);
int			check_map(t_map *map);
int			map_builder(char **int_map, int scale, t_map *map,
				t_player *player);
int			**resize_matrix(int **matrix, int *width);
int			**get_image_matrix(char *data, int width, int height);
t_texture	*get_texture(t_texture *textures, int type);

bool	parse_map(int argv, char **argc, char **map, t_cub *cub)
{
	if (argv != 2)
		return (EXIT_FAILURE);
	if (ft_strlen(argc[1]) < 4
		|| ft_strncmp(argc[1] + (ft_strlen(argc[1]) - 4), ".cub", 5))
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

bool	validate_map(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	char	**map;
	int		num_line;
	int		num_textures;
	int		data_type;

	init_cub(cub);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map = malloc(sizeof(char **));
	num_line = 0;
	num_textures = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' '
				|| line[0] == '\t'))
		{
			cub->map.max_y += 1;
			if (ft_strlen(line) > cub->map.max_x)
				cub->map.max_x = ft_strlen(line);
			map[num_line++] = get_int_array(line);
			if (is_player(line))
			{
				cub->player.matrix_pos.x = is_player(line);
				cub->player.matrix_pos.y = num_line;
			}
			map = ft_realloc(map, sizeof(char **) * (num_line + 1));
		}
		else
		{
			data_type = get_data_type(line);
			if (data_type == NO || data_type == SO || data_type == WE
				|| data_type == EA)
			{
				if (add_texture(line, cub->map.textures, &cub->screen,
						data_type) == EXIT_FAILURE)
				{
					free(line);
					return (EXIT_FAILURE);
				}
			}
			if (data_type == F)
				cub->map.bottom_color = color_parser(line);
			if (data_type == C)
				cub->map.top_color = color_parser(line);
			free(line);
		}
		line = get_next_line(fd);
	}
//	printf("size: %d %d\n", cub->map.max_x, cub->map.max_y);
	map[num_line] = NULL;
	if (check_map(&cub->map))
		return (EXIT_FAILURE);
	if (valid_map_from_player((int)cub->player.matrix_pos.x,
			(int)cub->player.matrix_pos.y, map, cub->map.max_y,
			cub->map.max_x))
		map_builder(map, MAPSCALE, &cub->map, &cub->player);
	return (EXIT_SUCCESS);
}

bool	valid_map_from_player(int x, int y, char **map, int max_x, int max_y)
{
	int				its;
	static int		**checker;
	static int		recursive_deep;

	its = 0;
	checker = NULL;
	recursive_deep = 0;
	// HARCODE
	return (1);
	recursive_deep++;
	if (checker == NULL)
		checker = empty_map(max_x, max_y);
	if (checker[y][x] == '1')
		return (0);
	checker[y][x] = '1';
	if (map[y][x] == '1')
		return (0);
	if (x > 0)
		its += valid_map_from_player(x - 1, y, map, max_x, max_y);
	if (x < max_x)
		its += valid_map_from_player(x + 1, y, map, max_x, max_y);
	if (y > 0)
		its += valid_map_from_player(x, y - 1, map, max_x, max_y);
	if (y < max_y)
		its += valid_map_from_player(x, y + 1, map, max_x, max_y);
	if ((x == 0 || x == max_x) && map[y][x] == '0')
		return (1);
	if ((y == 0 || y == max_y) && map[y][x] == '0')
		return (1);
	if (its)
		return (1);
	return (0);
}

int	**empty_map(int max_x, int max_y)
{
	int	i;
	int	j;
	int	**array;

	array = (int **)malloc(max_x * sizeof(int *));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (i++ < max_x)
	{
		array[i] = (int *)malloc(max_y * sizeof(int));
		if (array[i] == NULL)
		{
			j = -1;
			while (j++ < i)
				free(array[j]);
			free(array);
			return (NULL);
		}
	}
	return (array);
}
