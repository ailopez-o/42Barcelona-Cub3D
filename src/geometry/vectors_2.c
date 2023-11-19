/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:11:18 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/19 18:19:39 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>

float	vector_to_angle(t_vector vector)
{
	double	angulo;

	angulo = atan2(vector.dir[Y], vector.dir[X]) * 180 / M_PI;
	if (angulo < 0)
		angulo += 360;
	return (angulo);
}

t_vector	get_unit_vector(t_point p1, t_point p2)
{
	t_point		point;
	t_vector	vect;
	float		magnitude;

	point.x = p2.x - p1.x;
	point.y = p2.y - p1.y;
	magnitude = sqrt(point.x * point.x + point.y * point.y);
	vect.dir[X] = point.x / magnitude;
	vect.dir[Y] = point.y / magnitude;
	return (vect);
}

t_vector	get_geo_vector(char geo)
{
	t_vector	vect;

	if (geo == 'N')
	{
		vect.dir[X] = 0;
		vect.dir[Y] = -1;
	}
	if (geo == 'S')
	{
		vect.dir[X] = 0;
		vect.dir[Y] = 1;
	}
	if (geo == 'E')
	{
		vect.dir[X] = 1;
		vect.dir[Y] = 0;
	}
	if (geo == 'W')
	{
		vect.dir[X] = -1;
		vect.dir[Y] = 0;
	}
	return (vect);
}
