/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:50:12 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/30 10:50:17 by framos-p         ###   ########.fr       */
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
	printf("Num textures \t [%d]\n", num);
	num = 0;
	while (map->objets[num].valid)
		num++;
	printf("Num objets \t [%d]\n", num);
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

void	free_image(t_img *img)
{
	int	i;

	i = 0;
	while (i < img->width)
	{
		free(img->matrix[i]);
		i++;
	}
	free(img->matrix);
}

void	free_textures(t_texture *textures)
{
	int	i;

	i = 0;
	while (textures[i].valid)
	{
		free(textures[i].path);
		free_image(&textures[i].img);
		i++;
	}
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		j = 0;
		write(1, "\n", 1);
		i++;
	}
}
