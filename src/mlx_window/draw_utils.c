/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:20:48 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/20 01:50:47 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>
#include "vectors.h"

int			ft_round(double num);
int			gradient(int startcolor, int endcolor, int len, int pix);
void		draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color);
int 		oscurecer_color(int color_hex, int iteraciones);
float		norm_distancia(int dist);
float		vector_to_angle(t_vector vector);
t_vector	get_unit_vector(t_point p1, t_point p2);

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

void	draw_3d_line(t_mlx *screen, t_player play, t_colision *colision, int iter)
{
	t_point		start;
	t_point		end;
	t_vector	vector_ray = get_unit_vector(play.pos, colision->point);
	t_vector	vector_playr = play.front;
	float		angulo_player = vector_to_angle(play.front);
	float		angulo_ray = vector_to_angle(vector_ray);
	float		line_size = ((WINY / colision->distance * 50) / 2);
	float		new_distance;
	
	
	int line_height = (int)(WINY / (colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) * 100);


	if (iter == 0)
		printf("\rangulo ply: %f, ang ray %f, diferencia %f, lo que necesitamos : a = cos(ß) * h = %f * %f = %f", angulo_player, angulo_ray, angulo_player - angulo_ray, cos((angulo_player - angulo_ray) * M_PI / 180), colision->distance, cos((angulo_player - angulo_ray) * M_PI / 180) * colision->distance);
	start.x = WINX - iter;
	start.y = (-line_height / 2 + WINY / 2);
	// start.y = WINY / 2 - ((colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) / 2);
	start.color = oscurecer_color(0xE83535, colision->distance);
	end.x = WINX - iter;
	end.y = (line_height / 2 + WINY / 2);
	// end.y = WINY / 2 + ((colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) / 2);
	if (colision->distance > 900)
		end.y = WINY;
	end.color = oscurecer_color(0xE83535, colision->distance);



	draw_line(screen, start, end);
}



void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions)
{
	static int	iter = 0;

	while (colisions->valid)
	{
		pos.color = WHITE;
		colisions->point.color = ROJO;
		draw_line(screen, pos, colisions->point);
		draw_3d_line(screen, cub->player, colisions, iter);
		colisions++;
		iter++;
		if (iter > WIN2D)
			iter = 0;
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

void draw_objets(t_mlx *screen, t_objet *objets)
{
	while(objets->type == WALL)
	{
		draw_polygon(screen, &objets->polygon);
		objets++;
	}
}

int oscurecer_color(int color_hex, int iteraciones)
{
	if (iteraciones > 900)
		return (BGCOLOR);
    int r = (color_hex >> 16) & 0xFF;
    int g = (color_hex >> 8) & 0xFF;
    int b = color_hex & 0xFF;

    // Escalar el número de iteraciones de 0-300
    float escala = (float)iteraciones / 920.0;
    if (escala > 1.0) escala = 1.0;

    // Calcular el decremento en función de la escala
    int decremento = (int)(escala * 255.0);

    r -= decremento;
    g -= decremento;
    b -= decremento;

    // Si la escala es mayor que 1, establecer el color a negro
    if (escala >= 1.0) {
        r = 0;
        g = 0;
        b = 0;
    }

    // Asegurarse de que los componentes RGB no sean menores que 0
    r = (r < 0) ? 0 : r;
    g = (g < 0) ? 0 : g;
    b = (b < 0) ? 0 : b;
    
    return (r << 16) | (g << 8) | b;
}

float	norm_distancia(int dist)
{
	return (dist / 675);
}

float angle_between_lines(t_line l1, t_line l2)
{
    t_point v1 = {l1.p2.x - l1.p1.x, l1.p2.y - l1.p1.y};
    t_point v2 = {l2.p2.x - l2.p1.x, l2.p2.y - l2.p1.y};
    float dot_product = v1.x*v2.x + v1.y*v2.y;
    float magnitude_v1 = sqrt(pow(v1.x, 2) + pow(v1.y, 2));
    float magnitude_v2 = sqrt(pow(v2.x, 2) + pow(v2.y, 2));
    float angle = acos(dot_product / (magnitude_v1 * magnitude_v2));
    return angle;
}
