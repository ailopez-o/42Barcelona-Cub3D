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

void	initialize_player(char **map_arr, t_map *map, t_player *player,
						int scale)
{
	player->pos.x = player->matrix_pos.x * scale + (scale / 2);
	player->pos.y = player->matrix_pos.y * scale + (scale / 2);
	player->front = get_geo_vector((char)player->init_view);
	player->cam = player->front;
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
