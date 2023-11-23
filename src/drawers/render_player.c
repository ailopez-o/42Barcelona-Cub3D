/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:37:59 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 18:04:30 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "math.h"
#include "geometry.h"
#include <sys/time.h>

int		render(void *param);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos,
			t_colision *colisions);
void	draw_objets(t_mlx *screen, t_objet *objets, float scale);

void	player_position(t_cub *cub)
{
	t_vector	ortogonal;

	if ((cub->player.move & 0x01) == GO_FRONT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(cub->player.front), cub->player.player_speed);
	if ((cub->player.move & 0x02) == GO_BACK)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, 180)),
				cub->player.player_speed);
	if ((cub->player.move & 0x04) == GO_RIGHT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, -90)),
				cub->player.player_speed);
	if ((cub->player.move & 0x08) == GO_LEFT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, 90)),
				cub->player.player_speed);
	if (cub->player.rotate == ROTATE_R)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front,
					-cub->player.player_rot_speed));
	if (cub->player.rotate == ROTATE_L)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front,
					cub->player.player_rot_speed));
	if (cub->player.rotate)
		cub->player.cam = cub->player.front;
}

void	draw_player(t_mlx *screen, t_player player, float scale)
{
	t_point	scaled_pos;

	scaled_pos = player.pos;
	scaled_pos.x *= scale + 10;
	scaled_pos.y *= scale;
	draw_circle(screen, scaled_pos, 3, VERDE);
}

void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos,
			t_colision *colisions)
{
	int			iter;
	t_point		point;
	float		scale;
	float		mapwidth;
	float		mapheight;

	mapwidth = cub->map.max_x;
	mapheight = cub->map.max_y;
	iter = 0;
	if (mapwidth > mapheight)
		scale = (MINIMAPSCALE) / mapwidth;
	else
		scale = (MINIMAPSCALE) / mapheight;
	while (colisions->valid)
	{
		pos.color = RAY_COLOR_START;
		colisions->point.color = RAY_COLOR_END;
		point = colisions->point;
		point.x = point.x * scale + 10;
		point.y = point.y * scale + 10;
		draw_line(screen, pos, point);
		iter++;
		colisions++;
	}
}

void	draw_objets(t_mlx *screen, t_objet *objets, float scale)
{
	while (objets->type == WALL)
	{
		draw_polygon(screen, objets->polygon, scale);
		objets++;
	}
}
