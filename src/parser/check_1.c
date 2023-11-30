/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:55:26 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/30 12:07:02 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		validate_map(char *path, t_cub *cub);
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
bool		valid_map_from_player(int x, int y, char **map, int max_x,
				int max_y);
int			print_map(char **map);

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

bool	validate_map(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	char	**map;
	int		num_line;
	int		num_textures;
	int		data_type;
	bool	map_parsing;

	init_cub(cub);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error("Failed opening map\n"));
	map = ft_calloc(sizeof(char **), 1);
	map_parsing = false;
	num_line = 0;
	num_textures = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' '))
		{
			if (map_parsing == true || line_has_wall(line) == true)
			{
				map_parsing = true;
				cub->map.max_y += 1;
				if (ft_strlen(line) > cub->map.max_x)
					cub->map.max_x = ft_strlen(line);
				map[num_line] = get_int_array(line);
				num_line++;
				if (is_player(line))
				{
					cub->player.matrix_pos.x = is_player(line);
					cub->player.matrix_pos.y = num_line;
				}
				map = ft_realloc(map, sizeof(char **) * (num_line + 1));
			}
		}
		else
		{
			if (map_parsing == true)
				break;
			data_type = get_data_type(line);
			if (data_type == NO || data_type == SO || data_type == WE
				|| data_type == EA)
			{
				if (add_texture(line, cub->map.textures, &cub->screen,
						data_type) == EXIT_FAILURE)
					return (error("Failed adding texture\n"));
			}
			if (data_type == F)
				cub->map.bottom_color = color_parser(line);
			if (data_type == C)
				cub->map.top_color = color_parser(line);
		}
		line = get_next_line(fd);
	}
	printf("size: %d %d\n", cub->map.max_x, cub->map.max_y);
	map[num_line] = NULL;
	square_map(map, cub->map.max_x);
	if (check_map(&cub->map))
		return (error("Not all items needed\n"));
	if (valid_map_from_player((int)cub->player.matrix_pos.x,
			(int)cub->player.matrix_pos.y, map, cub->map.max_x,
			cub->map.max_y))
	{
		map_builder(map, MAPSCALE, &cub->map, &cub->player);
		return (EXIT_SUCCESS);
	}
	else
		return (error("Failed checking closed map\n"));
}

void	dfs(int x, int y, int ancho, int alto, char **map, bool *encerrado,
			char **visitado)
{
	int	i;
	int	nx;
	int	ny;

	if (x <= 0 || y <= 0 || x >= (ancho - 1) || y >= (alto - 1))
	{
		*encerrado = false;
		return ;
	}
	visitado[y][x] = true;
	ancho = ft_strlen(map[y]);
	int	dx[] = {0, 0, -1, 1};
	int	dy[] = {-1, 1, 0, 0};
	i = -1;
	while (++i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && ny >= 0 && nx <= ancho && ny <= alto && !visitado[ny][nx]
				&& map[ny][nx] == '0')
			dfs(nx, ny, ancho, alto, map, encerrado, visitado);
	}
}

bool	valid_map_from_player(int x, int y, char **map, int width, int height)
{
	char	**visited;
	int		i;
	int		j;
	bool	closed;

	visited = ft_calloc(sizeof(bool *), height);
	i = -1;
	while (++i < height)
	{
		visited[i] = ft_calloc(sizeof(bool), width);
		j = -1;
		while (++j < width)
			visited[i][j] = false;
	}
	closed = true;
	dfs(x, y, width, height, map, &closed, visited);
	i = -1;
	while (++i < height)
		free(visited[i]);
	free(visited);
	return (closed);
}
