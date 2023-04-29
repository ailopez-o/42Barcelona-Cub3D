/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:35:03 by bmoll             #+#    #+#             */
/*   Updated: 2023/04/28 18:57:42 by bmoll-pe         ###   ########.fr       */
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
	int		i, j;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "My Image");
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	img_data = mlx_get_data_addr(img_ptr, NULL, NULL, NULL);

	// Copiar los datos de la matriz en el buffer de la imagen
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, matrix[i][j]);
		}
	}
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
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
		if (!matrix[i])
			return (NULL);
		j = -1;
		while (++j < height)
		{
			//printf("%d %d | %d %d ==== data[%ld]\n", i, j, width, height, ((j * width + (i * sizeof(int)))));
			// matrix[i][j] = 0;
			// matrix[i][j] = matrix[i][j] | data[(j * width + (i * sizeof(int)))] << 24;//			1110 0000
			// matrix[i][j] = matrix[i][j] | data[(j * width + (i * sizeof(int))) + 1] << 16;//	 OR 0000 1001
			// matrix[i][j] = matrix[i][j] | data[(j * width + (i * sizeof(int))) + 2] << 8;//		---------
			// matrix[i][j] = matrix[i][j] | data[(j * width + (i * sizeof(int))) + 3];//			1110 1001
			matrix[i][j] = ((int *)data)[(j * width + i)];
		}
	}
	// matrix_printer(matrix, width, height);
	return (matrix);
}

int	*get_texture_column(t_line *wall, t_point point)
{
	double	line_length = distance_between_points(wall->p1, wall->p2);
	double	texture_repeats = line_length / wall->texture->width;
	double	point_distance = distance_between_points(wall->p1, point);
	double	point_position = point_distance / line_length;
	int		column_index = (int)(point_position * wall->texture->width * texture_repeats) % wall->texture->width;

	return (wall->texture->img.matrix[column_index]);
}

char	*ft_str_trim(char *str) 
{
	int		start;
	int		end;
	char	*new_str;
	
	end = ft_strlen(str) - 1;
	start = 0;
	while (str[start] == ' ')
		start++;
	while (str[end] == ' ' || str[end] == '\n')
		end--;
	if (end < start)
		return (ft_strdup(""));
	new_str = ft_substr(str, start, end - start +  1);
	return (new_str);
}