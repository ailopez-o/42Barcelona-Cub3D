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

t_line	vector_to_line(t_vector vector, t_point pos, int steps)
{
	t_line	line;

	line.p1 = pos;
	line.p2.x = pos.x + steps * vector.dir[X];
	line.p2.y = pos.y + steps * vector.dir[Y];
	return (line);
}
