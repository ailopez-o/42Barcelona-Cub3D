#include "defines.h"

float	angle_between_lines(t_line l1, t_line l2)
{
	t_point	v1;
	t_point	v2;
	float	dot_product;
	float	magnitude_v1;
	float	magnitude_v2;
	float	angle;

	v1.x = l1.p2.x - l1.p1.x;
	v1.y = l1.p2.y - l1.p1.y;
	v2.x = l2.p2.x - l2.p2.x;
	v2.y = l2.p2.y - l2.p2.y;
	dot_product = v1.x * v2.x + v1.y * v2.y;
	magnitude_v1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
	magnitude_v2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
	angle = acos(dot_product / (magnitude_v1 * magnitude_v2));
	return (angle);
}

bool	is_horizontal(t_line line)
{
	if (line.p1.x == line.p2.x)
		return(true);
	return(false);
}

bool	is_vertical(t_line line)
{
	if (line.p1.y == line.p2.y)
		return(true);
	return(false);
}

double	distance_between_points(t_point p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
