/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailopez- <ailopez-@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:51:43 by ailopez-          #+#    #+#             */
/*   Updated: 2023/11/30 17:32:47 by framos-p         ###   ########.fr       */
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
//void			map_builder(char **map_arr, int scale, t_map *map,
//				t_player *player);
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

void find_player_position(char **map_arr, t_player *player, int scale, char target)
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

void initialize_player(char **map_arr, t_map *map, t_player *player, int scale)
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

bool check_objet_init(int current, int pre, int col)
{
	if ((current == '1' && col == 0) || (current == '1' && col != 0 && pre == '0'))
		return true;
	return false;
}

bool check_objet_end(int current, int pre, int col)
{
	if ((current != '1' && col > 0 && pre == '1'))
		return true;
	return false;
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
			if (check_objet_init(map_arr[d.row][d.col], map_arr[d.row][d.col - 1], d.col) == true)
				create_wall_object(map, d.scaner, scale);
			if (check_objet_end(map_arr[d.row][d.col], map_arr[d.row][d.col - 1], d.col) == true)
				create_empty_space_object(map, d.scaner, scale, &d.num_obj);
			d.scaner.x += scale;
		}
		d.col = -1;
		d.scaner.x = 0;
		d.scaner.y += scale;
	}
	return (EXIT_SUCCESS);
}
/*
int	map_builder(char **map_arr, int scale, t_map *map, t_player *player)
{
	t_mapdata	d;

	printf("Starting map_builder...\n");
	initialize_player(map_arr, map, player, scale);
	printf("Player initialized.\n");
	d.num_obj = 0;
	d.row = -1;
	d.col = -1;
	d.scaner.x = 0;
	d.scaner.y = 0;
	d.c = map_arr[d.row][++d.col];
	while (map_arr[++d.row])
	{
		printf("Processing row %d...\n", d.row);
		while (d.c != 0)
		{
			if ((d.c == '1' && d.col == 0) || (d.c == '1' && d.col != 0
					&& map_arr[d.row][d.col - 1] == '0'))
				create_wall_object(map, d.scaner, scale);
			if ((d.c == '0' && d.col > 0 && map_arr[d.row][d.col - 1] == '1')
					|| (d.c == '0' && map_arr[d.row][d.col + 1] == '1'
					&& map_arr[d.row][d.col + 1] == '0'))
				create_empty_space_object(map, d.scaner, scale, &d.num_obj);
			d.scaner.x += scale;
		}
		printf("End of row %d processing.\n", d.row);
		d.col = -1;
		d.scaner.x = 0;
		d.scaner.y += scale;
	}
	printf("Exiting map_builder...\n");
	return (EXIT_SUCCESS);
}
*/
/*
int	map_builder(char **map_arr, int scale, t_map *map, t_player *player)
{
	int			num_obj;
	int			row;
	int			col;
	t_point		scaner;

	num_obj = 0;
	while (map->objets[num_obj].valid)
		num_obj++;
	scaner.x = 0;
	scaner.y = 0;
	row = 0;
	col = 0;
	while (map_arr[row])
	{
		while (map_arr[row][col] != 0)
		{
			if (map_arr[row][col] == 'N' || map_arr[row][col] == 'S'
				|| map_arr[row][col] == 'W' || map_arr[row][col] == 'E')
			{
				player->pos.x = scaner.x;
				player->pos.y = scaner.y;
				player->front = get_geo_vector((char)map_arr[row][col]);
				player->cam = player->front;
			}
			if ((map_arr[row][col] == '1' && col == 0) || (map_arr[row][col]
					== '1' && col != 0 && map_arr[row][col - 1] == '0'))
			{
				map->objets[num_obj].valid = 1;
				map->objets[num_obj].is_collider = 1;
				map->objets[num_obj].type = WALL;
				map->objets[num_obj].polygon.color = SUPERAZUL;
				map->objets[num_obj].polygon.line[0].texture
					= get_texture(map->textures, NO);
				map->objets[num_obj].polygon.line[1].texture
					= get_texture(map->textures, EA);
				map->objets[num_obj].polygon.line[2].texture
					= get_texture(map->textures, SO);
				map->objets[num_obj].polygon.line[3].texture
					= get_texture(map->textures, WE);
				map->objets[num_obj].polygon.line[0].p1.x = scaner.x;
				map->objets[num_obj].polygon.line[0].p1.y = scaner.y;
				map->objets[num_obj].polygon.line[3].p1.x = scaner.x;
				map->objets[num_obj].polygon.line[3].p1.y = scaner.y + scale;
				map->objets[num_obj].polygon.line[3].p2
					= map->objets[num_obj].polygon.line[0].p1;
			}
			if ((map_arr[row][col] == '0' && col > 0 && map_arr[row][col - 1]
					== '1') || (map_arr[row][col + 1] == '1'
					&& map_arr[row][col + 1] == '0'))
			{
				map->objets[num_obj].polygon.line[0].p2.x = scaner.x;
				map->objets[num_obj].polygon.line[0].p2.y = scaner.y;
				map->objets[num_obj].polygon.line[1].p1
					= map->objets[num_obj].polygon.line[0].p2;
				map->objets[num_obj].polygon.line[1].p2.x = scaner.x;
				map->objets[num_obj].polygon.line[1].p2.y = scaner.y + scale;
				map->objets[num_obj].polygon.line[2].p1
					= map->objets[num_obj].polygon.line[1].p2;
				map->objets[num_obj].polygon.line[2].p2.x
					= map->objets[num_obj].polygon.line[0].p1.x;
				map->objets[num_obj].polygon.line[2].p2.y = scaner.y + scale;
				num_obj++;
			}
			scaner.x += scale;
			col++;
		}
		free(map_arr[row]);
		col = 0;
		row++;
		scaner.x = 0;
		scaner.y += scale;
	}
	free(map_arr);
	return (EXIT_SUCCESS);
}*/
