/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:46:37 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:46:43 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>
#include "geometry.h"

int		*get_texture_column(t_line *wall, t_point point);
int		*get_texture_column_fix(t_colision *colision);
int		*get_texture_column(t_line *wall, t_point point);
int		*get_texture_column_fix(t_colision *colision);
int		calculate_new_height(double distance, int texture_height);
int		*create_new_column(int new_height);
void	populate_new_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height);
void	populate_larger_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height);
int		*adjust_column_if_greater_than_winy(int *new_column, double distance,
			int *new_height);

/*
*	This function generates the color of each pixel between starcolor and
*	endcolor.To do that get the RGB chanels independtly and create a 
*	linear escale between each channel.
*	The function return the color number "pix" of line "0->len".

	// if (iteraciones > PLYVIEW)
	// 	return (BGCOLOR);
	// // Escalar el número de iteraciones de 0-300
	// float escala = (float)iteraciones / PLYVIEW;
	// if (escala > 1.0) escala = 1.0;
	// Calcular el decremento en función de la escala
	//int decremento = (int)(escala * 255.0);
	// Si la escala es mayor que 1, establecer el color a negro
	// if (escala >= 1.0) {
	// 	r = 0;
	// 	g = 0;
	// 	b = 0;
	// }
	// Asegurarse de que los componentes RGB no sean menores que 0
*/

int	color_fade(int color_hex, int value)
{
	int	r;
	int	g;
	int	b;

	r = (color_hex >> 16) & 0xFF;
	g = (color_hex >> 8) & 0xFF;
	b = color_hex & 0xFF;
	r -= value;
	g -= value;
	b -= value;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

float	norm_distancia(int dist)
{
	return (dist / 675);
}

void	*ft_intmemcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned int		*str_dest;
	const unsigned int	*str_src;

	str_dest = dest;
	str_src = src;
	i = 0;
	if (dest == src)
		return (dest);
	while (n > i)
	{
		str_dest[i] = str_src[i];
		i++;
	}
	return (dest);
}

void	rotate_texture(int *column, int height)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = height - 1;
	while (i < j)
	{
		tmp = column[i];
		column[i] = column[j];
		column[j] = tmp;
		i++;
		j--;
	}
}

int	*adjust_column_if_greater_than_winy(int *new_column, double distance,
		int *new_height)
{
	int	*cuted;

	if (distance > WINY)
	{
		cuted = ft_calloc(sizeof(int), distance - (distance - WINY));
		if (cuted == NULL)
			return (NULL);
		ft_intmemcpy(cuted, new_column + (int)((distance - WINY) / 2), distance
			- (distance - WINY));
		free(new_column);
		new_column = cuted;
		*new_height = WINY;
		cuted = NULL;
	}
	return (new_column);
}
