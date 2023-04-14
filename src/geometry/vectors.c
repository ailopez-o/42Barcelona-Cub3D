#include "defines.h"
#include "math.h"

t_point get_colision(t_line wall, t_line ray);

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


t_point *get_dir_ray_colider(t_point pos, t_vector dir, int wide, t_line wall)
{
	t_vector	scan_vector;
	t_point		colision;
	t_point 	*ray_colider;
	int			ang;
	int			num_colision;

	ang = 0;
	num_colision = 0;
	scan_vector = rotate_vector(dir, - wide/2);
	ray_colider = malloc(sizeof(t_point) * (wide + 1));
	while (ang < wide)
	{
		colision = get_colision(wall, vector_to_line(scan_vector, pos, 10));
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


t_point *get_ray_colider(t_point pos, t_line wall)
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
		colision = get_colision(wall, vector_to_line(scan_vector, pos, 10));
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

t_point get_colision(t_line wall, t_line ray)
{

	float		den;
	float		t;
	float		u;
	t_point		colision;

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