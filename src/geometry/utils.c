#include "defines.h"

float	angle_between_lines(t_line l1, t_line l2)
{
	t_point v1 = {l1.p2.x - l1.p1.x, l1.p2.y - l1.p1.y};
	t_point v2 = {l2.p2.x - l2.p1.x, l2.p2.y - l2.p1.y};
	float dot_product = v1.x*v2.x + v1.y*v2.y;
	float magnitude_v1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
	float magnitude_v2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
	float angle = acos(dot_product / (magnitude_v1 * magnitude_v2));
	return angle;
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