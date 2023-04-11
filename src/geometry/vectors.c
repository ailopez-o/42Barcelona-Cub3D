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