/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:04:44 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 16:19:28 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "drawers.h"
#include "geometry.h"

typedef struct s_params
{
	t_mlx	*screen;
	t_point	start;
	t_point	end;
	int		*column;
	bool	b_shadow;
}	t_params;

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

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	pixels = sqrt(delta.x * delta.x + delta.y * delta.y);
	len = pixels;
	delta.x /= pixels;
	delta.y /= pixels;
	pixel = start;
	while (pixels--)
	{
		pixel.color = gradient(start.color, end.color, len, len - pixels);
		my_pixel_put(screen, pixel);
		pixel.x += delta.x;
		pixel.y += delta.y;
	}
}

void	draw_line_pixels(t_params *params)
{
	t_point	delta;
	t_point	pixel;

	delta.x = (params->end.x - params->start.x) / (sqrt(pow(params->end.x
					- params->start.x, 2) + pow(params->end.y
					- params->start.y, 2)));
	delta.y = (params->end.y - params->start.y) / (sqrt(pow(params->end.x
					- params->start.x, 2) + pow(params->end.y
					- params->start.y, 2)));
	pixel.x = params->start.x;
	pixel.y = params->start.y;
	while (sqrt(pow(params->end.x - pixel.x, 2) + pow(params->end.y
				- pixel.y, 2)) > 0)
	{
		pixel.color = *(params->column);
		if (params->b_shadow)
			pixel.color = color_fade(pixel.color, 40);
		my_pixel_put(params->screen, pixel);
		pixel.x += delta.x;
		pixel.y += delta.y;
		(params->column)++;
	}
}

void	draw_texture_line(t_mlx *screen, t_line stripe, int *column,
			bool b_shadow)
{
	t_params	params;

	if (stripe.p1.y < 0)
		stripe.p1.y = 0;
	if (stripe.p1.y > WINY)
		stripe.p1.y = WINY;
	if (stripe.p2.y < 0)
		stripe.p2.y = 0;
	if (stripe.p2.y > WINY)
		stripe.p2.y = WINY;
	params.screen = screen;
	params.start = stripe.p1;
	params.end = stripe.p2;
	params.column = column;
	params.b_shadow = b_shadow;
	draw_line_pixels(&params);
}

void	draw_circle(t_mlx *screen, t_point center, int radius, int color)
{
	t_point	drawer;
	float	distance;

	drawer.color = color;
	drawer.y = center.y - radius;
	while (drawer.y <= center.y + radius)
	{
		drawer.x = center.x - radius;
		while (drawer.x <= center.x + radius)
		{
			distance = sqrt((drawer.x - center.x) * (drawer.x - center.x)
					+ (drawer.y - center.y) * (drawer.y - center.y));
			if (distance <= radius)
				my_pixel_put(screen, drawer);
			drawer.x++;
		}
		drawer.y++;
	}
}

void	draw_polygon(t_mlx *screen, t_polygon polygon, float scale)
{
	int	side;

	side = -1;
	while (++side < 4)
	{
		polygon.line[side].p1.color = polygon.color;
		polygon.line[side].p2.color = polygon.color;
		polygon.line[side].p1.x = polygon.line[side].p1.x * scale;
		polygon.line[side].p1.y = polygon.line[side].p1.y * scale;
		polygon.line[side].p2.x = polygon.line[side].p2.x * scale;
		polygon.line[side].p2.y = polygon.line[side].p2.y * scale;
		draw_line(screen, polygon.line[side].p1, polygon.line[side].p2);
	}
}
