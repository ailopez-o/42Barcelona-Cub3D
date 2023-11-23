/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:59:48 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 18:03:05 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "math.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3d(t_cub *cub);
void	render_column(t_cub *cub, float angulo_player, t_colision *colision,
			int iter);
float	calculate_orto_dist(float angulo_player, float angulo_ray,
			t_colision *colision);
float	calculate_line_height(float orto_dist, float fov_dist);
void	initialize_stripe(t_line *stripe, t_colision *colision, int iter,
			float line_height);
void	draw_textures_and_shadow(t_cub *cub, t_line *stripe,
			t_colision *colision, float line_height);

void	render_3d(t_cub *cub)
{
	float		angulo_player;
	t_colision	*colision;
	int			iter;

	angulo_player = vector_to_angle(cub->player.cam);
	colision = cub->player.ray_colider;
	iter = 0;
	while (colision->valid)
	{
		render_column(cub, angulo_player, colision, iter);
		colision++;
		iter++;
	}
}

void	render_column(t_cub *cub, float angulo_player, t_colision *colision,
			int iter)
{
	t_line		stripe;
	t_vector	vector_ray;
	float		angulo_ray;
	float		orto_dist;
	float		line_height;

	vector_ray = get_unit_vector(cub->player.pos, colision->point);
	angulo_ray = vector_to_angle(vector_ray);
	orto_dist = calculate_orto_dist(angulo_player, angulo_ray, colision);
	line_height = calculate_line_height(orto_dist, cub->fov_dist);
	initialize_stripe(&stripe, colision, iter, line_height);
	draw_textures_and_shadow(cub, &stripe, colision, line_height);
}

float	calculate_orto_dist(float angulo_player, float angulo_ray,
			t_colision *colision)
{
	return (colision->distance * cos((angulo_player - angulo_ray)
			* M_PI / 180));
}

float	calculate_line_height(float orto_dist, float fov_dist)
{
	return ((int)((MAPSCALE / orto_dist) * fov_dist));
}
