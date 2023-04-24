/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:44:01 by bmoll             #+#    #+#             */
/*   Updated: 2023/04/21 21:36:28 by bmoll            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "time.h"
#include "drawers.h"
#include "geometry.h"
#include <sys/time.h>

void	moove_player(t_cub *cub, int key)
{
	t_vector	ortogonal;

	if (key == KEY_W || key == KEY_UP)
		cub->player.pos = move_player_vector(cub, cub->player.front, PLYSPEED);
	if (key == KEY_S || key == KEY_DOWN)
		cub->player.pos = move_player_vector(cub, rotate_vector(cub->player.front, 180), PLYSPEED);
	if (key == KEY_A)
	{
		ortogonal = rotate_vector(cub->player.front, 90);
		cub->player.pos = move_player_vector(cub, ortogonal, PLYSPEED);
	}
	if (key == KEY_D)
	{
		ortogonal = rotate_vector(cub->player.front, -90);
		cub->player.pos = move_player_vector(cub, ortogonal, PLYSPEED);
	}
}

void	turn_player(t_cub *cub, int key)
{
	if (key == KEY_LEFT)
	{
		cub->player.front = rotate_vector(cub->player.front, PLYSPEED);
		cub->player.cam = cub->player.front;
	}
	if (key == KEY_RIGHT)
	{
		cub->player.front = rotate_vector(cub->player.front, -PLYSPEED);
		cub->player.cam = cub->player.front;
	}
}
