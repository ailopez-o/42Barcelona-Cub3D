/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:55:26 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/15 15:25:01 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		open_map_file(char *path, int *fd);
int			parse_map_file(int fd, t_cub *cub, char ***map, t_pars *pars);
bool		square_map(char **map, int max_x);
int			check_map(t_map *map);
bool		valid_map_from_player(t_data *data);
int			map_builder(char **int_map, int scale, t_map *map,
				t_player *player);
int			free_double(char **matrix);

int	initialize_data_struct(t_data *data, t_cub *cub, char **map)
{
	data->x = (int)cub->player.matrix_pos.x;
	data->y = (int)cub->player.matrix_pos.y;
	data->width = cub->map.max_x;
	data->height = cub->map.max_y;
	data->map = map;
	data->closed = true;
	return (0);
}

void	init_vars(t_pars *pars, t_cub *cub)
{
	pars->num_line = 0;
	pars->num_line = 0;
	pars->num_textures = 0;
	pars->data_type = 0;
	pars->map_parsing = false;
	init_cub(cub);
}

int	validate_map(char *path, t_cub *cub)
{
	t_pars	pars;
	int		fd;
	char	**map;
	t_data	data;
	int		ret;

	init_vars(&pars, cub);
	if (!open_map_file(path, &fd))
		return (EXIT_FAILURE);
	map = ft_calloc(sizeof(char **), 1);
	if (map == NULL)
		return (EXIT_FAILURE);
	if (parse_map_file(fd, cub, &map, &pars) == EXIT_FAILURE)
		return (map[pars.num_line] = NULL, free_double(map), EXIT_FAILURE);
	map[pars.num_line] = NULL;
	square_map(map, cub->map.max_x);
	if (check_map(&cub->map))
		return (error("Not all items needed\n"));
	if (initialize_data_struct(&data, cub, map) == -1)
		return (EXIT_FAILURE);
	if (valid_map_from_player(&data))
		return (map_builder(map, MAPSCALE, &cub->map, &cub->player),
			free_double(map));
	else
		return (free_double(map), error("Failed checking closed map\n"));
}

void	dfs(t_data *data, int x, int y)
{
	int			i;
	int			nx;
	int			ny;
	static int	dx[] = {0, 0, -1, 1};
	static int	dy[] = {-1, 1, 0, 0};

	if (x <= 0 || y <= 0 || x >= (data->width - 1) || y >= (data->height - 1))
	{
		data->closed = false;
		return ;
	}
	data->visited[y][x] = true;
	data->width = ft_strlen(data->map[y]);
	i = -1;
	while (++i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		if (nx >= 0 && ny >= 0 && nx <= data->width && ny <= data->height
			&& !(data->visited[ny][nx]) && data->map[ny][nx] == '0')
			dfs(data, nx, ny);
	}
}

bool	valid_map_from_player(t_data *data)
{
	int	i;
	int	j;

	data->visited = ft_calloc(sizeof(char *), data->height);
	if (data->visited == NULL)
		return (false);
	i = -1;
	while (++i < data->height)
	{
		data->visited[i] = ft_calloc(sizeof(char), data->width);
		if (data->visited[i] == NULL)
			return (false);
		j = -1;
		while (++j < data->width)
			data->visited[i][j] = false;
	}
	dfs(data, data->x, data->y);
	i = -1;
	while (++i < data->height)
		free(data->visited[i]);
	free(data->visited);
	return (data->closed);
}
