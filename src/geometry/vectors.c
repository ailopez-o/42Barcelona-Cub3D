#include "defines.h"
#include "math.h"



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

