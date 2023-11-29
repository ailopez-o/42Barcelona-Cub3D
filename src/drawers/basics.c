/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:23:51 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 16:19:33 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "drawers.h"
#include "geometry.h"

void	my_pixel_put(t_mlx *screen, t_point pixel)
{
	size_t	calc;

	if ((int)pixel.x >= WINX || (int)pixel.x < 0)
		return ;
	if ((int)pixel.y >= WINY || (int)pixel.y < 0)
		return ;
	pixel.y = WINY - pixel.y;
	calc = (WINX * 4 * ((int)pixel.y - 1)) + ((int)pixel.x * 4);
	screen->img_buff[calc] = pixel.color & 0xff;
	screen->img_buff[calc + 1] = (pixel.color >> 8) & 0xff;
	screen->img_buff[calc + 2] = (pixel.color >> 16) & 0xff;
}

void	clear_screen(t_mlx *screen, int color)
{
	t_point	cleaner;

	cleaner.x = 0;
	cleaner.y = 0;
	cleaner.color = color;
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

/*
 * draw_vector - draws a vector on the screen
 *
 * @screen: pointer to the screen
 * @vector: the vector to be drawn
 * @pos: the starting point of the vector
 * @color: the color of the vector to be drawn
*/

void	draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color)
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
