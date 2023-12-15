/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:11:24 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/30 11:26:26 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"

double	distance_between_points(t_point p1, t_point p2);
char	*ft_str_trim(char *str);
void	*ft_realloc(void *ptr, size_t size);

void	matrix_printer(int **matrix, int width, int height)
{
	t_ptr	ptr;
	int		i;
	int		j;

	ptr.mlx_ptr = mlx_init();
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, width, height, "My Image");
	ptr.img_ptr = mlx_new_image(ptr.mlx_ptr, width, height);
	ptr.img_data = mlx_get_data_addr(ptr.img_ptr, NULL, NULL, NULL);
	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
			mlx_pixel_put(ptr.mlx_ptr, ptr.win_ptr, i, j, matrix[i][j]);
	}
	mlx_loop(ptr.mlx_ptr);
}

int	**get_image_matrix(char *data, int width, int height)
{
	int		**matrix;
	int		i;
	int		j;

	i = -1;
	matrix = malloc(sizeof(int *) * width);
	if (!matrix)
		return (NULL);
	while (++i < width)
	{
		matrix[i] = malloc(sizeof(int) * height);
		if (matrix[i] == NULL)
			return (NULL);
		if (!matrix[i])
			return (NULL);
		j = -1;
		while (++j < height)
			matrix[i][j] = ((int *)data)[(j * width + i)];
	}
	return (matrix);
}

int	**resize_matrix(int **matrix, int *width)
{
	int	**scaled_columns;
	int	i;

	scaled_columns = ft_calloc(sizeof(int *), MAPSCALE);
	if (scaled_columns == NULL)
		return (NULL);
	i = -1;
	while (++i < MAPSCALE)
		scaled_columns[i] = matrix[i * *width / MAPSCALE];
	free(matrix);
	*width = MAPSCALE;
	return (scaled_columns);
}

int	*get_texture_column(t_line *wall, t_point point)
{
	double	line_length;
	double	texture_repeats;
	double	point_distance;
	double	point_position;
	int		column_index;

	line_length = distance_between_points(wall->p1, wall->p2);
	texture_repeats = line_length / wall->texture->width;
	point_distance = distance_between_points(wall->p1, point);
	point_position = point_distance / line_length;
	column_index = (int)(point_position * MAPSCALE * texture_repeats)
		% MAPSCALE;
	return (wall->texture->img.matrix[column_index]);
}
