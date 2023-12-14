/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:07:13 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/14 16:46:42 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		validate_map(char *path, t_cub *cub);
int			get_int_array(char *line);
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
bool		valid_map_from_player(t_data *data);

int	get_int_array(char *line)
{
	char	*char_line;
	int		num_col;

	num_col = 0;
	while (line[num_col])
	{
		if (line[num_col] == ' ')
			line[num_col] = '0';
		if (line[num_col] == '\n')
			line[num_col] = '0';
		num_col++;
	}
	return (EXIT_SUCCESS);
}

int	get_data_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] && line[i] == 'N' && line[i + 1] && line[i + 1] == 'O'
		&& line[i + 2] && line[i + 2] == ' ')
		return (NO);
	if (line[i] && line[i] == 'S' && line[i + 1] && line[i + 1] == 'O'
		&& line[i + 2] && line[i + 2] == ' ')
		return (SO);
	if (line[i] && line[i] == 'W' && line[i + 1] && line[i + 1] == 'E'
		&& line[i + 2] && line[i + 2] == ' ')
		return (WE);
	if (line[i] && line[i] == 'E' && line[i + 1] && line[i + 1] == 'A'
		&& line[i + 2] && line[i + 2] == ' ')
		return (EA);
	if (line[i] && line[i] == 'C' && line[i + 1] && line[i + 1] == ' ')
		return (C);
	if (line[i] && line[i] == 'F' && line[i + 1] && line[i + 1] == ' ')
		return (F);
	return (0);
}

/*
int	get_data_type(char *line)
{
	if (line[0] && line[0] == 'N' && line[1] && line[1] == 'O' && line[2]
		&& line[2] == ' ')
		return (NO);
	if (line[0] && line[0] == 'S' && line[1] && line[1] == 'O' && line[2]
		&& line[2] == ' ')
		return (SO);
	if (line[0] && line[0] == 'W' && line[1] && line[1] == 'E' && line[2]
		&& line[2] == ' ')
		return (WE);
	if (line[0] && line[0] == 'E' && line[1] && line[1] == 'A' && line[2]
		&& line[2] == ' ')
		return (EA);
	if (line[0] && line[0] == 'S' && line[1] && line[1] == 'C' && line[2]
		&& line[2] == ' ')
		return (SC);
	if (line[0] && line[0] == 'C' && line[1] && line[1] == ' ')
		return (C);
	if (line[0] && line[0] == 'F' && line[1] && line[1] == ' ')
		return (F);
	return (0);
}
*/
int	add_texture(char *path, t_texture *textures, t_mlx *screen, int type)
{
	char	*str_trimed;

	while (textures->valid == true)
		textures++;
	str_trimed = ft_str_trim(path + 3);
	textures->path = ft_substr(str_trimed, 0, ft_strlen(path) - 1);
	free(str_trimed);
	textures->img.ptr = mlx_xpm_file_to_image(screen->handler, textures->path,
			&textures->width, &textures->height);
	if (textures->img.ptr == NULL)
		return (EXIT_FAILURE);
	textures->img.addr = mlx_get_data_addr(textures->img.ptr, NULL, NULL, NULL);
	if (textures->img.addr == NULL)
		return (EXIT_FAILURE);
	textures->valid = true;
	textures->type = type;
	textures->img.matrix = resize_matrix(get_image_matrix(textures->img.addr,
				textures->width, textures->height), &textures->width);
	textures->img.width = textures->width;
	textures->img.height = textures->height;
	return (EXIT_SUCCESS);
}

int	check_map(t_map *map)
{
	if (!get_texture(map->textures, NO))
		return (EXIT_FAILURE);
	if (!get_texture(map->textures, SO))
		return (EXIT_FAILURE);
	if (!get_texture(map->textures, WE))
		return (EXIT_FAILURE);
	if (!get_texture(map->textures, EA))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
