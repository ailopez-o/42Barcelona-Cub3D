#include "defines.h"
#include "math.h"
#include "vectors.h"


t_colision get_colision(t_line wall, t_point pos, t_vector ray_vect);
t_colision get_closest_colision(t_objet *objet, t_point pos, t_vector ray_vect);
t_line	*get_polygon_lines(t_polygon polygon);
float get_distance(t_point p1, t_point p2);

t_colision *get_dir_ray_collider(t_point pos, t_vector dir, int wide, t_objet *objets)
{
	t_vector	scan_vector;
	t_colision	colision;
	t_colision 	*ray_colider;
	float		ang;
	float		step;
	int			num_colision;

	ang = 0;
	num_colision = 0;
	scan_vector = rotate_vector(dir, - wide/2);
	ray_colider = malloc(sizeof(t_colision) * (WIN2D + 1));
	while (ang < (float)wide)
	{
		colision = get_closest_colision(objets, pos, scan_vector);
		if (colision.valid)
			ray_colider[num_colision++] = colision;
		ang += ((float) wide / WIN2D);
		scan_vector = rotate_vector(scan_vector, ((float) wide / WIN2D));
	}
	// printf("num_hits %d\n", num_colision);
	return (ray_colider);
}

t_colision get_colision(t_line wall, t_point pos, t_vector ray_vect)
{
	float		den;
	float		t;
	float		u;
	t_line		ray;
	t_colision	colision;

	colision.valid = false;
	ray = vector_to_line(ray_vect, pos, 10);
	den = (wall.p1.x - wall.p2.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y - wall.p2.y) * (ray.p1.x - ray.p2.x);
	if (den == 0)
		return (colision);
	t = ((wall.p1.x - ray.p1.x) * (ray.p1.y - ray.p2.y) - (wall.p1.y - ray.p1.y) * (ray.p1.x - ray.p2.x)) / den;
	u = -((wall.p1.x - wall.p2.x) * (wall.p1.y - ray.p1.y) - (wall.p1.y - wall.p2.y) * (wall.p1.x - ray.p1.x)) / den;
	if (t > 0 && t <1 && u > 0)
	{
		colision.point.x = wall.p1.x + t * (wall.p2.x - wall.p1.x);
		colision.point.y = wall.p1.y + t * (wall.p2.y - wall.p1.y);
		colision.line = wall;
		colision.distance = get_distance(pos, colision.point);
		colision.valid = true;
	}
	return (colision);
}

t_colision get_closest_colision(t_objet *objet, t_point pos, t_vector ray_vect)
{
	t_colision	closest_colision;
	t_colision	colision;
	float		dist;
	float		closest_dist;
	int			side;
	t_line		*lines;

	closest_dist = 10000000;
	closest_colision.valid = false;
	while (objet->type == WALL)
	{
		side = 0;
		lines = get_polygon_lines(objet->polygon);
		while(side < 4)
		{
			colision = get_colision(lines[side], pos, ray_vect);
			if (colision.valid)
			{
				dist = get_distance(pos, colision.point);
				if (dist < closest_dist)
				{
					closest_dist = dist;
					closest_colision = colision;
				}
			}
			side++;
		}
		free(lines);
		objet++;
	}
	return (closest_colision);
}


t_line	*get_polygon_lines(t_polygon polygon)
{
	t_line *line;

	line = malloc(sizeof(t_line) * 4);
	line[0].p1 = polygon.p1;
	line[0].p2 = polygon.p2;
	line[1].p1 = polygon.p2;
	line[1].p2 = polygon.p3;
	line[2].p1 = polygon.p3;
	line[2].p2 = polygon.p4;
	line[3].p1 = polygon.p4;
	line[3].p2 = polygon.p1;
	return (line);
}

float get_distance(t_point p1, t_point p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}