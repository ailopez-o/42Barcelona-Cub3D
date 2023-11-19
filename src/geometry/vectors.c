/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:06:10 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/19 18:19:38 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>

t_colision	get_closest_colision(t_objet *objet, t_point pos,
				t_vector ray_vect);

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

t_point	go_vector(t_point init, t_vector vector, int steps)
{
	t_point	new_point;

	new_point.x = init.x + vector.dir[X] * steps;
	new_point.y = init.y + vector.dir[Y] * steps;
	return (new_point);
}

t_point	move_player_vector(t_cub *cub, t_vector vector, int steps)
{
	uint16_t	iter;
	t_point		new_point;
	t_colision	colision;
	t_vector	tmp_vector;
	float		value;

	iter = 0;
	new_point.x = cub->player.pos.x;
	new_point.y = cub->player.pos.y;
	while (iter <= steps)
	{
		tmp_vector.dir[X] = vector.dir[X];
		tmp_vector.dir[Y] = 0.0;
		colision = get_closest_colision(cub->map.objets, new_point, tmp_vector);
		value = new_point.x + vector.dir[X];
		if (fabs(value - colision.point.x) > PLYCOLLIDE)
			new_point.x += vector.dir[X];
		tmp_vector.dir[X] = 0;
		tmp_vector.dir[Y] = vector.dir[Y];
		colision = get_closest_colision(cub->map.objets, new_point, tmp_vector);
		value = new_point.y + vector.dir[Y];
		if (fabs(value - colision.point.y) > PLYCOLLIDE)
			new_point.y += vector.dir[Y];
		iter++;
	}
	return (new_point);
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
//	vector.dir[0] + vector.dir[1];
	if (sum > 1.0)
	{
		vector.dir[X] /= sum;
		vector.dir[Y] /= sum;
	}
	return (vector);
}

// t_vector normalize_vector(t_vector vector)
// {
// 	float 	factor;
// 	t_point	abs_point;

// 	abs_point.x = vector.dir[X];
// 	if (vector.dir[X] < 0)
// 		abs_point.x = - vector.dir[X];
// 	abs_point.y = vector.dir[Y];
// 	if (vector.dir[Y] < 0)
// 		abs_point.y = - vector.dir[Y];
// 	factor = abs_point.y;
// 	if (abs_point.x > abs_point.y)
// 		factor = abs_point.x;
// 	vector.dir[X] = vector.dir[X]/factor;
// 	vector.dir[Y] = vector.dir[Y]/factor;
// 	return (vector);
// }

t_line	vector_to_line(t_vector vector, t_point pos, int steps)
{
	t_line	line;

	line.p1 = pos;
	line.p2.x = pos.x + steps * vector.dir[X];
	line.p2.y = pos.y + steps * vector.dir[Y];
	return (line);
}
