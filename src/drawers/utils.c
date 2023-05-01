/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:20:48 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/05/01 13:32:47 by bmoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>
#include "geometry.h"

int			ft_round(double num);

/*
*	This function generates the color of each pixel between starcolor and endcolor
*	To do that get the RGB chanels independtly and create a 
*	linear escale between each channel.
*	The function return the color number "pix" of line "0->len".
*/

int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((endcolor >> 16) - \
					(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
					((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - (startcolor & 0xFF)) \
					/ (double)len;
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
}

int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}



int color_fade(int color_hex, int value)
{
	// if (iteraciones > PLYVIEW)
	// 	return (BGCOLOR);
	int r = (color_hex >> 16) & 0xFF;
	int g = (color_hex >> 8) & 0xFF;
	int b = color_hex & 0xFF;

	// // Escalar el número de iteraciones de 0-300
	// float escala = (float)iteraciones / PLYVIEW;
	// if (escala > 1.0) escala = 1.0;

	// Calcular el decremento en función de la escala
	//int decremento = (int)(escala * 255.0);

	r -= value;
	g -= value;
	b -= value;

	// // Si la escala es mayor que 1, establecer el color a negro
	// if (escala >= 1.0) {
	// 	r = 0;
	// 	g = 0;
	// 	b = 0;
	// }

	// Asegurarse de que los componentes RGB no sean menores que 0
	r = (r < 0) ? 0 : r;
	g = (g < 0) ? 0 : g;
	b = (b < 0) ? 0 : b;
	
	return (r << 16) | (g << 8) | b;
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
	int i;
	int j;
	int tmp;

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

int		*adjust_column(t_colision *colision, double distance)
{
	int *new_column;
	int *cuted;
	int new_height;

    if (distance < colision->line.texture->height)
    {
        new_height = (int)(colision->line.texture->height * distance / (double)colision->line.texture->height);
        new_column = malloc(new_height * sizeof(int));
        if (!new_column)
            return NULL;
        for (int i = 0; i < new_height; i++)
            new_column[i] = colision->line_texture[i * colision->line.texture->height / new_height];
    }
    else
    {
        new_height = (int)distance;
        new_column = malloc(new_height * sizeof(int));
        if (!new_column)
            return NULL;
        for (int i = 0; i < new_height; i++)
            new_column[i] = colision->line_texture[i * colision->line.texture->height / new_height % colision->line.texture->height];
    }
	if (distance > WINY)
	{
		cuted = ft_calloc(sizeof(int), distance - (distance - WINY));
		ft_intmemcpy(cuted, new_column + (int)((distance - WINY) / 2), distance - (distance - WINY));
		free(new_column);
		new_column = cuted;
		new_height = WINY;
		cuted = NULL;
	}
	if (new_column)
		rotate_texture(new_column, new_height);
	return (new_column);
}
