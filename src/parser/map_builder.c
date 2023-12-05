/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:11:22 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/04 11:15:03 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "mlx.h"
#include "geometry.h"
#include "parser.h"

void		*ft_realloc(void *ptr, size_t size);
int			*get_int_array(char *line);
int			map_builder(char **map_arr, int scale, t_map *map,
				t_player *player);
int			**get_image_matrix(char *data, int width, int height);
void		matrix_printer(int **matrix, int width, int height);
int			get_data_type(char *line);
int			add_texture(char *path, t_texture *textures, t_mlx *screen,
				int type);
void		print_map_resume(t_map *map);
int			color_parser(char *line);
int			check_map(t_map *map);
t_texture	*get_texture(t_texture *textures, int type);
int			**resize_matrix(int **matrix, int *width);
void		find_player_position(char **map_arr, t_player *player, int scale,
				char target);
void		initialize_player(char **map_arr, t_map *map, t_player *player,
				int scale);
void		init_wall_object(t_objet *obj, t_texture *textures, t_point scaner,
				int scale);

void	create_wall_object(t_map *map, t_point scaner, int scale)
{
	int	num_obj;

	num_obj = 0;
	while (map->objets[num_obj].valid)
		num_obj++;
	if (!map->objets[num_obj].valid && !map->objets[num_obj].is_collider)
		init_wall_object(&map->objets[num_obj], map->textures, scaner, scale);
}

void	create_empty_space_object(t_map *map, t_point scaner, int scale,
			int *num_obj)
{
	if (*num_obj < 1000)
	{
		map->objets[*num_obj].polygon.line[0].p2.x = scaner.x;
		map->objets[*num_obj].polygon.line[0].p2.y = scaner.y;
		map->objets[*num_obj].polygon.line[1].p1
			= map->objets[*num_obj].polygon.line[0].p2;
		map->objets[*num_obj].polygon.line[1].p2.x = scaner.x;
		map->objets[*num_obj].polygon.line[1].p2.y = scaner.y + scale;
		map->objets[*num_obj].polygon.line[2].p1
			= map->objets[*num_obj].polygon.line[1].p2;
		map->objets[*num_obj].polygon.line[2].p2.x
			= map->objets[*num_obj].polygon.line[0].p1.x;
		map->objets[*num_obj].polygon.line[2].p2.y = scaner.y + scale;
		(*num_obj)++;
	}
}

bool	check_objet_init(int current, int pre, int col)
{
	if ((current == '1' && col == 0) || (current == '1' && col != 0
			&& pre == '0'))
		return (true);
	return (false);
}

bool	check_objet_end(int current, int pre, int col)
{
	if ((current != '1' && col > 0 && pre == '1'))
		return (true);
	return (false);
}

int	map_builder(char **map_arr, int scale, t_map *map, t_player *player)
{
	t_mapdata	d;

	initialize_player(map_arr, map, player, scale);
	d.num_obj = 0;
	d.scaner.x = 0;
	d.scaner.y = 0;
	d.row = -1;
	d.col = -1;
	while (map_arr[++d.row])
	{
		while (map_arr[d.row][++d.col] != 0)
		{
			if (check_objet_init(map_arr[d.row][d.col],
				map_arr[d.row][d.col - 1], d.col) == true)
				create_wall_object(map, d.scaner, scale);
			if (check_objet_end(map_arr[d.row][d.col],
				map_arr[d.row][d.col - 1], d.col) == true)
				create_empty_space_object(map, d.scaner, scale, &d.num_obj);
			d.scaner.x += scale;
		}
		d.col = -1;
		d.scaner.x = 0;
		d.scaner.y += scale;
	}
	return (EXIT_SUCCESS);
}
