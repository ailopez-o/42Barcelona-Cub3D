/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:51:43 by ailopez-          #+#    #+#             */
/*   Updated: 2023/12/04 11:14:10 by framos-p         ###   ########.fr       */
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

void	find_player_position(char **map_arr, t_player *player, int scale,
			char target)
{
	t_point	scaner;
	int		row;
	int		col;

	scaner.x = 0;
	scaner.y = 0;
	row = -1;
	col = -1;
	while (map_arr[++row])
	{
		while (map_arr[row][++col] != 0)
		{
			if (map_arr[row][col] == target)
			{
				player->pos.x = scaner.x;
				player->pos.y = scaner.y;
				player->front = get_geo_vector((char)target);
				player->cam = player->front;
			}
			scaner.x += scale;
		}
		col = 0;
		scaner.x = 0;
		scaner.y += scale;
	}
}

void	initialize_player(char **map_arr, t_map *map, t_player *player,
			int scale)
{
	find_player_position(map_arr, player, scale, 'N');
	find_player_position(map_arr, player, scale, 'S');
	find_player_position(map_arr, player, scale, 'W');
	find_player_position(map_arr, player, scale, 'E');
}

void	init_wall_object(t_objet *obj, t_texture *textures, t_point scaner,
			int scale)
{
	obj->valid = 1;
	obj->is_collider = 1;
	obj->type = WALL;
	obj->polygon.color = SUPERAZUL;
	obj->polygon.line[0].texture = get_texture(textures, NO);
	obj->polygon.line[1].texture = get_texture(textures, EA);
	obj->polygon.line[2].texture = get_texture(textures, SO);
	obj->polygon.line[3].texture = get_texture(textures, WE);
	obj->polygon.line[0].p1.x = scaner.x;
	obj->polygon.line[0].p1.y = scaner.y;
	obj->polygon.line[3].p1.x = scaner.x;
	obj->polygon.line[3].p1.y = scaner.y + scale;
	obj->polygon.line[3].p2 = obj->polygon.line[0].p1;
}
