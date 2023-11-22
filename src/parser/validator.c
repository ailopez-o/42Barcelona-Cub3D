/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:50:15 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 11:56:11 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

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

char	*get_int_array(char *line)
{
	char	*char_line;
	int		num_col;

	char_line = ft_calloc(sizeof(char), ft_strlen(line) + 1);
	num_col = 0;
	while (line[num_col])
	{
		if (line[num_col] == '1')
			char_line[num_col] = '1';
		else if (line[num_col] == 'N')
			char_line[num_col] = 'N';
		else if (line[num_col] == 'S')
			char_line[num_col] = 'S';
		else if (line[num_col] == 'E')
			char_line[num_col] = 'E';
		else if (line[num_col] == 'W')
			char_line[num_col] = 'W';
		else
			char_line[num_col] = '0';
		num_col++;
	}
	return (char_line);
}

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

int	add_texture(char *path, t_texture *textures, t_mlx *screen, int type)
{
	char	*str_trimed;

	while (textures->valid == true)
		textures++;
	str_trimed = ft_str_trim(path + 3);
	textures->path = ft_substr(str_trimed, 0, ft_strlen(path) - 1);
	free (str_trimed);
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
	return (EXIT_SUCCESS);
	//Mirar si hace falta realloc
}

int	color_parser(char *line)
{
	char	*trim_line;
	char	**splitted;
	int		color[3];
	int		hex;

	trim_line = ft_str_trim(line + 1);
	splitted = ft_split(trim_line, ',');
	color[0] = ft_atoi(splitted[0]);
	color[1] = ft_atoi(splitted[1]);
	color[2] = ft_atoi(splitted[2]);
	hex = color[0] << 16 | color[1] << 8 | color[2];
	free(trim_line);
	free (splitted[0]);
	free (splitted[1]);
	free (splitted[2]);
	free (splitted);
	return (hex);
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
