#include "defines.h"
#include "math.h"
#include "vectors.h"

int			ft_round(double num);
int			gradient(int startcolor, int endcolor, int len, int pix);
void		draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color);

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

void	draw_ray_collider(t_mlx *screen, t_point pos, t_point *coliders)
{
	while (coliders->x != -1)
	{
		pos.color = WHITE;
		coliders->color = ROJO;
		draw_line(screen, pos, *coliders);
		coliders++;
	}

}

void	draw_player(t_mlx *screen, t_player player)
{
	draw_circle(screen, player.pos, 5, VERDE);
	draw_vector(screen, player.front, player.pos, VERDE);
	draw_vector(screen, player.cam, player.pos, ROJO);
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

int	ft_round(double num)
{
	int	rounded;

	rounded = (int)num;
	if (num - rounded >= .5)
		rounded++;
	return (rounded);
}


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

void draw_walls(t_mlx *screen,t_line *walls)
{
	while(walls->p1.x != -1)
	{
		walls->p1.color = ROJO;
		walls->p2.color = ROJO;
		draw_line(screen, walls->p1, walls->p2);
		walls++;
	}
}
