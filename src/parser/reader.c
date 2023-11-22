/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:32:35 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 10:39:50 by framos-p         ###   ########.fr       */
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

void	print_map_resume(t_map *map)
{
	int	num;

	num = 0;
	while (map->textures[num].valid)
		num++;
//	printf("Num textures \t [%d]\n", num);
	num = 0;
	while (map->objets[num].valid)
		num++;
//	printf("Num objets \t [%d]\n", num);
}

t_texture	*get_texture(t_texture *textures, int type)
{
	while (textures->valid)
	{
		if (textures->type == type)
			return (textures);
		textures++;
	}
	return (NULL);
}

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
			if ((map_arr[row][col] == '1' && col == 0)
				|| (map_arr[row][col] == '1' && col != 0
				&& map_arr[row][col - 1] == '0'))
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
			if ((map_arr[row][col] == '0' && col > 0
				&& map_arr[row][col - 1] == '1')
				|| (map_arr[row][col + 1] == '1'
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
		col = 0;
		row++;
		scaner.x = 0;
		scaner.y += scale;
	}
	return (EXIT_SUCCESS);
}
