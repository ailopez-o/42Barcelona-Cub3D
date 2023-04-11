#include "defines.h"
#include "math.h"


int	ft_round(double num);

t_ray normalize_ray(t_ray ray);

void	my_pixel_put(t_mlx *screen, t_point pixel)
{
	size_t	calc;

	if ((int)pixel.x > WINX || (int)pixel.x < 0)
		return ;
	if ((int)pixel.y > WINY || (int)pixel.y < 0)
		return ;
	calc = (WINX * 4 * ((int)pixel.y - 1)) + ((int)pixel.x * 4);
	screen->img_buff[calc] = pixel.color & 0xff;
	screen->img_buff[calc + 1] = (pixel.color >> 8) & 0xff;
	screen->img_buff[calc + 2] = (pixel.color >> 16) & 0xff;
}

/*
*	This function generates the color of each pixel between starcolor and endcolor
*	To do that get the RGB chanels independtly and create a 
*	linear escale between each channel.
*	The function return the color number "pix" of line "0->len".
*/

int	gradient(int startcolor, int endcolor, int len, int pix)
{
	double	increment[3];
	int		new[3];
	int		newcolor;

	increment[0] = (double)((endcolor >> 16) - \
					(startcolor >> 16)) / (double)len;
	increment[1] = (double)(((endcolor >> 8) & 0xFF) - \
					((startcolor >> 8) & 0xFF)) / (double)len;
	increment[2] = (double)((endcolor & 0xFF) - (startcolor & 0xFF)) \
					/ (double)len;
	new[0] = (startcolor >> 16) + ft_round(pix * increment[0]);
	new[1] = ((startcolor >> 8) & 0xFF) + ft_round(pix * increment[1]);
	new[2] = (startcolor & 0xFF) + ft_round(pix * increment[2]);
	newcolor = (new[0] << 16) + (new[1] << 8) + new[2];
	return (newcolor);
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

	// if (valid_pixel(start) == 0 && valid_pixel(end) == 0)
	// 	return (0);
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


int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}


void draw_ray(t_mlx *screen, t_ray ray)
{
	t_line	ray_line;
	
	ray = normalize_ray(ray);
	ray_line.p1 = ray.pos;
	ray_line.p2.x = ray.pos.x + ray.dir[X] * 50;
	ray_line.p2.y = ray.pos.y - ray.dir[Y] * 50;
	ray_line.p1.color = VERDE;
	ray_line.p2.color = VERDE;
	draw_line(screen, ray_line.p1, ray_line.p2);
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

t_ray normalize_ray(t_ray ray)
{
	float 	factor;
	t_point	abs_point;

	abs_point.x = ray.dir[X];
	if (ray.dir[X] < 0)
		abs_point.x = - ray.dir[X];
	abs_point.y = ray.dir[Y];
	if (ray.dir[Y] < 0)
		abs_point.y = - ray.dir[Y];
	factor = abs_point.y;
	if (abs_point.x > abs_point.y)
		factor = abs_point.x;
	ray.dir[X] = ray.dir[X]/factor;
	ray.dir[Y] = ray.dir[Y]/factor;
	return (ray);
}