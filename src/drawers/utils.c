/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:20:48 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/25 12:35:00 by bmoll            ###   ########.fr       */
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



int color_fade(int color_hex, int iteraciones)
{
	if (iteraciones > PLYVIEW)
		return (BGCOLOR);
	int r = (color_hex >> 16) & 0xFF;
	int g = (color_hex >> 8) & 0xFF;
	int b = color_hex & 0xFF;

	// Escalar el número de iteraciones de 0-300
	float escala = (float)iteraciones / PLYVIEW;
	if (escala > 1.0) escala = 1.0;

	// Calcular el decremento en función de la escala
	int decremento = (int)(escala * 255.0);

	r -= decremento;
	g -= decremento;
	b -= decremento;

	// Si la escala es mayor que 1, establecer el color a negro
	if (escala >= 1.0) {
		r = 0;
		g = 0;
		b = 0;
	}

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

