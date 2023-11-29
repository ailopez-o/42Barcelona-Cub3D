/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:37:08 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:40:42 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

float	angle_between_lines(t_line l1, t_line l2)
{
	t_point	v1;
	t_point	v2;
	t_ray	ray;

	v1.x = l1.p2.x - l1.p1.x;
	v1.y = l1.p2.y - l1.p1.y;
	v2.x = l2.p2.x - l2.p2.x;
	v2.y = l2.p2.y - l2.p2.y;
	ray.dot_product = v1.x * v2.x + v1.y * v2.y;
	ray.magnitude_v1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
	ray.magnitude_v2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
	ray.angle = acos(ray.dot_product / (ray.magnitude_v1 * ray.magnitude_v2));
	return (ray.angle);
}

bool	is_horizontal(t_line line)
{
	if (line.p1.x == line.p2.x)
		return (true);
	return (false);
}

bool	is_vertical(t_line line)
{
	if (line.p1.y == line.p2.y)
		return (true);
	return (false);
}

double	distance_between_points(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
