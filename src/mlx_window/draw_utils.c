#include "defines.h"
#include "math.h"


int	ft_round(double num);

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


// void draw_square(t_mlx *screen, t_point center, int size)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	if (color == 0xFFA500)
// 	{
// 		cub->player->ply_x = x / cub->map->scale;
// 		cub->player->ply_y = y / cub->map->scale;
// 	}
// 	while (i < cub->map->scale)
// 	{
// 		j = 0;
// 		while (j < cub->map->scale)
// 		{
// 			my_pixel_put(cub->screen, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }