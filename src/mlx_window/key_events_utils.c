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

void	move_player(t_cub *cub, int key)
{
	t_vector	ortogonal;

	if (key == KEY_W || key == KEY_UP)
		cub->player.move = GO_FRONT;
	if (key == KEY_S || key == KEY_DOWN)
		cub->player.move = GO_BACK;
	if (key == KEY_A)
		cub->player.move = GO_LEFT;
	if (key == KEY_D)
		cub->player.move = GO_RIGHT;
}

void	turn_player(t_cub *cub, int key)
{
	if (key == KEY_LEFT)
		cub->player.rotate = ROTATE_L;
	if (key == KEY_RIGHT)
		cub->player.rotate = ROTATE_R;
}
