/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:11:18 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:43:20 by framos-p         ###   ########.fr       */
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

t_vector	rotate_vector(t_vector vector, float ang)
{
	float		radianes;
	t_vector	new_vector;

	radianes = ang * M_PI / 180.0;
	new_vector.dir[X] = cos(radianes) * vector.dir[X] - sin(radianes)
		* vector.dir[Y];
	new_vector.dir[Y] = sin(radianes) * vector.dir[X] + cos(radianes)
		* vector.dir[Y];
	return (new_vector);
}

/**
 * normalize_vector - normalizes a vector
 *
 * This function normalizes a given vector by dividing its direction
 * components by the largest component. This ensures that the magnitude
 * of the vector is equal to 1, and therefore the vector represents
 * only the direction of the original vector. The function returns
 * the normalized vector.
 *
 * @vector: the vector to be normalized
 *
 * Return: the normalized vector
 */

t_vector	normalize_vector(t_vector vector)
{
	float	magnitude;
	float	sum;

	magnitude = sqrt(vector.dir[X] * vector.dir[X] + vector.dir[Y]
			* vector.dir[Y]);
	vector.dir[X] /= magnitude;
	vector.dir[Y] /= magnitude;
	if (sum > 1.0)
	{
		vector.dir[X] /= sum;
		vector.dir[Y] /= sum;
	}
	return (vector);
}
