/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:20:44 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/19 23:54:11 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>

t_vector rotate_vector(t_vector vector, float ang)
{
	float		radianes;
	t_vector 	new_vector;
	
	radianes = ang * M_PI / 180.0;
	new_vector.dir[X] = cos(radianes) * vector.dir[X] - sin(radianes) * vector.dir[Y];
	new_vector.dir[Y] = sin(radianes) * vector.dir[X] + cos(radianes) * vector.dir[Y];
	return (new_vector);
}

t_point go_vector(t_point init, t_vector vector, int steps)
{
	t_point	new_point;

	new_point.x = init.x + vector.dir[X] * steps;
	new_point.y = init.y + vector.dir[Y] * steps;
	return (new_point);
}

t_vector normalize_vector(t_vector vector)
{
	float 	factor;
	t_point	abs_point;

	abs_point.x = vector.dir[X];
	if (vector.dir[X] < 0)
		abs_point.x = - vector.dir[X];
	abs_point.y = vector.dir[Y];
	if (vector.dir[Y] < 0)
		abs_point.y = - vector.dir[Y];
	factor = abs_point.y;
	if (abs_point.x > abs_point.y)
		factor = abs_point.x;
	vector.dir[X] = vector.dir[X]/factor;
	vector.dir[Y] = vector.dir[Y]/factor;
	return (vector);
}

t_line vector_to_line(t_vector vector, t_point pos, int steps)
{
	t_line line;

	line.p1 = pos;
	line.p2.x = pos.x + steps * vector.dir[X];
	line.p2.y = pos.y + steps * vector.dir[Y];
	return (line);
}

float vector_to_angle(t_vector vector)
{
	double	angulo;

	angulo = atan2(vector.dir[Y], vector.dir[X]) * 180 / M_PI;
	if (angulo < 0) {
		angulo += 360;
	}
	return angulo;
}

t_vector get_unit_vector(t_point p1, t_point p2)
{
    t_point		point;
    t_vector	vect;
    float		magnitude;

	// printf("puntos: (%f, %f) y (%f, %f)\n", p1.x, p1.y, p2.x, p2.y);
    point.x = p2.x - p1.x;
    point.y = p2.y - p1.y;
    magnitude = sqrt(point.x * point.x + point.y * point.y);
    vect.dir[X] = point.x / magnitude;
    vect.dir[Y] = point.y / magnitude;
	// printf("vector: (%f, %f)\n", vect.dir[X], vect.dir[Y]);
    return (vect);
}
