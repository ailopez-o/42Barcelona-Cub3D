#include "defines.h"
#include "drawers.h"
#include "geometry.h"





void	my_pixel_put(t_mlx *screen, t_point pixel)
{
	size_t	calc;

	if ((int)pixel.x > WINX || (int)pixel.x < 0)
		return ;
	if ((int)pixel.y > WINY || (int)pixel.y < 0)
		return ;
	pixel.y = WINY - pixel.y;
	calc = (WINX * 4 * ((int)pixel.y - 1)) + ((int)pixel.x * 4);
	screen->img_buff[calc] = pixel.color & 0xff;
	screen->img_buff[calc + 1] = (pixel.color >> 8) & 0xff;
	screen->img_buff[calc + 2] = (pixel.color >> 16) & 0xff;
}

/*
*	This function checks if the whole line is out of the window to avoid the 
*	operations and getting better the performance.
*	Then calculate all the point of the line with the Bresenham's line algorithm
*/

void	draw_line(t_mlx *screen, t_point start, t_point end)
{
	t_point	delta;
	t_point	pixel;
	int		pixels;
	int		len;

	if (start.y < 0)
		start.y = 0;
	if (start.y > WINY)
		start.y = WINY;
	if (end.y < 0)
		end.y = 0;
	if (end.y > WINY)
		end.y = WINY;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	pixels = sqrt((delta.x * delta.x) + \
			(delta.y * delta.y));
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = start.x;
	pixel.y = start.y;
	while (pixels > 0)
	{
		pixel.color = gradient(start.color, end.color, len, len - pixels);
		my_pixel_put(screen, pixel);
		pixel.x += delta.x;
		pixel.y += delta.y;
		pixels = pixels - 1;
	}
}

void draw_circle(t_mlx *screen, t_point center, int radius, int color)
{
	t_point	drawer;
	float	distance;

	drawer.color = color;
    for (drawer.y = center.y - radius; drawer.y <= center.y + radius; drawer.y++)
    {
        for (drawer.x = center.x - radius; drawer.x <= center.x + radius; drawer.x++)
        {
            distance = sqrt((drawer.x - center.x) * (drawer.x - center.x) + (drawer.y - center.y) * (drawer.y - center.y));
            if (distance <= radius)
            {
                my_pixel_put(screen, drawer);
            }
        }
    }
}

void clear_screen(t_mlx *screen)
{	
	t_point	cleaner;

	cleaner.x = 0;
	cleaner.y = 0;
	cleaner.color = BLACK;
	while (cleaner.y < WINY)
	{
		while (cleaner.x < WINX)
		{
			my_pixel_put(screen, cleaner);
			cleaner.x ++;
		}
		cleaner.y ++;
		cleaner.x = 0;
	}
}

void draw_polygon(t_mlx *screen, t_polygon *polygon)
{
	polygon->p1.color = polygon->color;
	polygon->p2.color = polygon->color;
	polygon->p3.color = polygon->color;
	polygon->p4.color = polygon->color;
	draw_line(screen, polygon->p1, polygon->p2);
	draw_line(screen, polygon->p2, polygon->p3);
	draw_line(screen, polygon->p3, polygon->p4);
	draw_line(screen, polygon->p4, polygon->p1);
}


/**
 * draw_vector - draws a vector on the screen
 *
 * @screen: pointer to the screen
 * @vector: the vector to be drawn
 * @pos: the starting point of the vector
 * @color: the color of the vector to be drawn
 */

void draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color)
{
	t_line	vector_line;
	
	vector = normalize_vector(vector);
	vector_line.p1 = pos;
	vector_line.p2.x = pos.x + vector.dir[X] * 50;
	vector_line.p2.y = pos.y + vector.dir[Y] * 50;
	vector_line.p1.color = color;
	vector_line.p2.color = color;
	draw_line(screen, vector_line.p1, vector_line.p2);
}
