/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:40:03 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 10:49:22 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"

double	distance_between_points(t_point p1, t_point p2);

void	matrix_printer(int **matrix, int width, int height)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		i;
	int		j;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "My Image");
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	img_data = mlx_get_data_addr(img_ptr, NULL, NULL, NULL);
	// Copiar los datos de la matriz en el buffer de la imagen
	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, matrix[i][j]);
	}
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

int	**get_image_matrix(char *data, int width, int height)
{
	int	**matrix;
	int	i;
	int	j;

	i = -1;
	matrix = malloc(sizeof(int *) * width);
	if (!matrix)
		return (NULL);
	while (++i < width)
	{
		matrix[i] = malloc(sizeof(int) * height);
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
	i = -1;
	while (++i < MAPSCALE)
	{
		scaled_columns[i] = matrix[i * *width / MAPSCALE];
		//printf("pos: %d\n", i * *width / MAPSCALE)
	}
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
	//int		column_index = (int)(point_position * wall->texture->width
	//* texture_repeats) % wall->texture->width;
	line_length = distance_between_points(wall->p1, wall->p2);
	texture_repeats = line_length / wall->texture->width;
	point_distance = distance_between_points(wall->p1, point);
	point_position = point_distance / line_length;
	column_index = (int)(point_position * MAPSCALE * texture_repeats)
		% MAPSCALE;
	return (wall->texture->img.matrix[column_index]);
}
