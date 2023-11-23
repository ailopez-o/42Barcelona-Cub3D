/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:54:16 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 17:56:39 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "math.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3d(t_cub *cub);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos,
			t_colision *colisions);
double	distance_between_points(t_point p1, t_point p2);
int		*adjust_column(t_colision *colision, double distance);
void	player_position(t_cub *cub);
void	render_map(t_cub *cub);
void	render_column(t_cub *cub, float angulo_player, t_colision *colision,
			int iter);
float	calculate_orto_dist(float angulo_player, float angulo_ray,
			t_colision *colision);
float	calculate_line_height(float orto_dist, float fov_dist);
void	initialize_stripe(t_line *stripe, t_colision *colision, int iter,
			float line_height);
void	draw_textures_and_shadow(t_cub *cub, t_line *stripe,
			t_colision *colision, float line_height);
void	render_map(t_cub *cub);
void	render_wall(t_cub *cub, t_objet object);
void	scale_and_draw_line(t_cub *cub, t_line line, int color);
float	determine_scale(float mapwidth, float mapheight);
t_point	scale_position(t_point position, float scale);

void	scale_polygon(t_polygon *poly, float scale)
{
	int	side;

	side = -1;
	while (++side < 4)
	{
		poly->line[side].p1.x = poly->line[side].p1.x * scale + 10;
		poly->line[side].p1.y = poly->line[side].p1.y * scale + 10;
		poly->line[side].p2.x = poly->line[side].p2.x * scale + 10;
		poly->line[side].p2.y = poly->line[side].p2.y * scale + 10;
	}
}

float	calculate_scale(float mapwidth, float mapheight)
{
	float	scale;

	if (mapwidth > mapheight)
		scale = (MINIMAPSCALE) / mapwidth;
	else
		scale = (MINIMAPSCALE) / mapheight;
	return (scale);
}

void	draw_objects(t_cub *cub, t_objet *objects, size_t iter)
{
	t_polygon	poly;
	float		scale;
	int			side;

	while (objects[iter].type == WALL)
	{
		poly = objects[iter].polygon;
		scale = calculate_scale(cub->map.max_x, cub->map.max_y);
		scale_polygon(&poly, scale);
		side = -1;
		while (++side < 4)
		{
			poly.line[side].p1.color = poly.color;
			poly.line[side].p2.color = poly.color;
			draw_line(&(cub->screen), poly.line[side].p1, poly.line[side].p2);
		}
		iter++;
	}
}

void	render_map(t_cub *cub)
{
	size_t	iter;
	t_objet	*objects;
	float	scale;
	t_point	scaled_pos;

	iter = 0;
	objects = cub->map.objets;
	draw_objects(cub, objects, iter);
	scaled_pos = cub->player.pos;
	scale = calculate_scale(cub->map.max_x, cub->map.max_y);
	scaled_pos.x = scaled_pos.x * scale + 10;
	scaled_pos.y = scaled_pos.y * scale + 10;
	draw_circle(&(cub->screen), scaled_pos, 3, PLAYER_COLOR);
	draw_ray_collider(cub, &(cub->screen), scaled_pos, cub->player.ray_colider);
}
