/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:35:03 by bmoll             #+#    #+#             */
/*   Updated: 2023/04/25 21:49:41 by bmoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"

void	matrix_printer(char **matrix, int width, int height)
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
			img_data[(j * width + i) * 4] = matrix[i][j];
			img_data[(j * width + i) * 4 + 1] = matrix[i][j];
			img_data[(j * width + i) * 4 + 2] = matrix[i][j];
			img_data[(j * width + i) * 4 + 3] = 0;
		}
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}

char	**get_image_matrix(char *data, int width, int height)
{
	char		**matrix;
	ssize_t		i;
	ssize_t		j;

	i = -1;
	matrix = malloc(sizeof(char *) * width);
	if (!matrix)
		return (NULL);
	while (++i < width)
	{
		matrix[i] = malloc(sizeof(char) * height);
		if (!matrix[i])
			return (NULL);
		j = -1;
		while (++j < height)
			matrix[i][j] = data[(j * width + i) * 4];
	}
	//matrix_printer(matrix, width, height);exit(0);
	return (matrix);
}
