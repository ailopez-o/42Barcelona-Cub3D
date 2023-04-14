#include "defines.h"
#include "math.h"
#include "vectors.h"


t_point get_colision(t_line wall, t_point pos, t_vector ray_vect);
t_point get_closest_colision(t_line *wall, t_point pos, t_vector ray_vect);
float distance(t_point p1, t_point p2);

t_point *get_dir_ray_collider(t_point pos, t_vector dir, int wide, t_line *wall)
{
	t_vector	scan_vector;
	t_point		colision;
	t_point 	*ray_colider;
	float		ang;
	float		step;
	int			num_colision;

	ang = 0;
	num_colision = 0;
	scan_vector = rotate_vector(dir, - wide/2);
	ray_colider = malloc(sizeof(t_point) * (WINX + 1));
	while (ang < (float)wide)
	{
		colision = get_closest_colision(wall, pos, scan_vector);
		if (colision.x != -1)
		{
			ray_colider[num_colision] = colision;
			num_colision++;
		}
		ang += ((float) wide / WINX);
		scan_vector = rotate_vector(scan_vector, ((float) wide / WINX));
	}
	ray_colider[num_colision].x = -1;
	ray_colider[num_colision].y = -1;
	return (ray_colider);
}


t_point *get_ray_collider(t_point pos, t_line *wall)
{
	t_vector	scan_vector;
	t_point		colision;
	t_point 	*ray_colider;
	int			ang;
	int			num_colision;

	ang = 0;
	num_colision = 0;
	scan_vector.dir[X] = 0;
	scan_vector.dir[Y] = 1;
	ray_colider = malloc(sizeof(t_point) * 361);
	while (ang < 360)
	{
		colision = get_closest_colision(wall, pos, scan_vector);
		if (colision.x != -1)
		{
			ray_colider[num_colision] = colision;
			num_colision++;
		}
		ang +=1;
		scan_vector = rotate_vector(scan_vector, 1);
	}
	ray_colider[num_colision].x = -1;
	ray_colider[num_colision].y = -1;
	return (ray_colider);
}

t_point get_colision(t_line wall, t_point pos, t_vector ray_vect)
{

	float		den;
	float		t;
	float		u;
	t_line		ray;
	t_point		colision;

	ray = vector_to_line(ray_vect, pos, 10);
	colision.x = -1;
	colision.y = -1;
	den = (wall.p1.x - wall.p2.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y - wall.p2.y) * (ray.p1.x - ray.p2.x);
	if (den == 0)
		return (colision);
	t = ((wall.p1.x - ray.p1.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y - ray.p1.y) * (ray.p1.x - ray.p2.x)) / den;
	u = -((wall.p1.x - wall.p2.x) * (wall.p1.y - ray.p1.y) - (wall.p1.y - wall.p2.y) * (wall.p1.x - ray.p1.x)) / den;
	if (t > 0 && t <1 && u > 0)
	{
		colision.x = wall.p1.x + t * (wall.p2.x - wall.p1.x);
		colision.y = wall.p1.y + t * (wall.p2.y - wall.p1.y);
	}
	return (colision);
}

t_point get_closest_colision(t_line *wall, t_point pos, t_vector ray_vect)
{
	t_point	closest_colision;
	t_point	colision;
	float	dist;
	float	closest_dist;

	closest_dist = 10000000;
	while(wall->p1.x != -1)
	{

		colision = get_colision(*wall, pos, ray_vect);
		if (colision.x != -1)
		{
			dist = distance(pos, colision);
			if (dist < closest_dist)
			{
				closest_dist = dist;
				closest_colision = colision;
			}
		}
		wall++;
	}
	return (closest_colision);
}

float distance(t_point p1, t_point p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}