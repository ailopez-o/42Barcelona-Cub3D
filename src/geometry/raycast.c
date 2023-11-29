/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:25:43 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:37:02 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "geometry.h"
#include <math.h>

t_colision	get_colision(t_line wall, t_point pos, t_vector ray_vect);
t_colision	get_closest_colision(t_objet *objet, t_point pos,
				t_vector ray_vect);
float		get_distance(t_point p1, t_point p2);
float		angle_between_lines(t_line l1, t_line l2);
int			*get_texture_column(t_line *wall, t_point point);
t_colision	check_collision(t_line *lines, t_point pos, t_vector ray_vect);

int	get_dir_ray_collider(t_player *player, int wide, t_objet *objets)
{
	t_vector	scan_vector;
	t_colision	colision;
	t_ray		ray;

	ray.ang = 0;
	ray.num_colision = 0;
	scan_vector = rotate_vector(player->cam, -wide / 2);
	while (ray.ang < (float)wide)
	{
		colision = get_closest_colision(objets, player->pos, scan_vector);
		if (colision.valid)
			player->ray_colider[ray.num_colision++] = colision;
		ray.ang += ((float)wide / WIN2D);
		scan_vector = rotate_vector(scan_vector, ((float)wide / WIN2D));
	}
	return (EXIT_SUCCESS);
}

t_colision	get_colision(t_line wall, t_point pos, t_vector ray_vect)
{
	float		den;
	float		t;
	float		u;
	t_line		ray;
	t_colision	colision;

	colision.valid = false;
	ray = vector_to_line(ray_vect, pos, 10);
	den = (wall.p1.x - wall.p2.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y
			- wall.p2.y) * (ray.p1.x - ray.p2.x);
	if (den == 0)
		return (colision);
	t = ((wall.p1.x - ray.p1.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y
				- ray.p1.y) * (ray.p1.x - ray.p2.x)) / den;
	u = -((wall.p1.x - wall.p2.x) * (wall.p1.y - ray.p1.y) - (wall.p1.y
				- wall.p2.y) * (wall.p1.x - ray.p1.x)) / den;
	if (t > 0 && t < 1 && u > 0)
	{
		colision.point.x = wall.p1.x + t * (wall.p2.x - wall.p1.x);
		colision.point.y = wall.p1.y + t * (wall.p2.y - wall.p1.y);
		colision.line = wall;
		colision.distance = get_distance(pos, colision.point);
		colision.valid = true;
	}
	return (colision);
}

/**
 * get_closest_colision - finds the closest collision between a ray and
 * WALL objects
 * * This function takes a pointer to the first `WALL` object in a 3D scene, the
 * starting position of a ray, and the direction of the ray as input. It then
 * iterates over each `WALL` object in the scene and checks for collisions
 * between the ray and each side of the object's polygon. If a collision is
 * found, the function calculates the distance between the collision point
 * and the starting position of the ray. The function then returns the closest
 * collision that was found.
 * @objet: A pointer to the first `WALL` object in the scene
 * @pos: The starting position of the ray
 * @ray_vect: The direction of the ray
 *
 * Return: The closest collision found between the ray and a `WALL`
 * object's polygon
 */

t_colision	check_collision(t_line *lines, t_point pos, t_vector ray_vect)
{
	t_colision	closest_colision;
	float		dist;
	int			side;
	t_colision	temp_colision;

	closest_colision.valid = false;
	closest_colision.distance = 10000000;
	side = -1;
	while (++side < 4)
	{
		temp_colision = get_colision(lines[side], pos, ray_vect);
		if (temp_colision.valid)
		{
			dist = get_distance(pos, temp_colision.point);
			if (dist < closest_colision.distance)
			{
				closest_colision = temp_colision;
				closest_colision.distance = dist;
			}
		}
	}
	return (closest_colision);
}

t_colision	get_closest_colision(t_objet *objet, t_point pos,
				t_vector ray_vect)
{
	t_colision	closest_colision;
	t_colision	colision;

	closest_colision.valid = false;
	closest_colision.distance = 10000000;
	while (objet->type == WALL)
	{
		colision = check_collision(objet->polygon.line, pos, ray_vect);
		if (colision.valid && colision.distance < closest_colision.distance)
			closest_colision = colision;
		objet++;
	}
	return (closest_colision);
}

float	get_distance(t_point p1, t_point p2)
{
	float	dx;
	float	dy;

	dy = p2.y - p1.y;
	dx = p2.x - p1.x;
	return (sqrt(dx * dx + dy * dy));
}
