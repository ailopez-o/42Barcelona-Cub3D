/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:10:09 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/30 11:10:28 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "parser.h"
#include <errno.h>
#include <string.h>

/**
 * init_cub - initialize the cub state object
 *
 * This function creates a new `t_line` object to represent the walls of the
 * game environment, initializes its position and color properties, and sets
 * the player's starting position and facing direction.
 *
 * @cub: a pointer to the `t_cub` object to initialize
 *
 * Return: true if initialization succeeds, false otherwise
 */

bool	init_cub(t_cub *cub)
{
	cub->player.pos.x = 700;
	cub->player.pos.y = 700;
	cub->player.front.dir[X] = 0;
	cub->player.front.dir[Y] = 1;
	cub->player.cam.dir[X] = 0;
	cub->player.cam.dir[Y] = 1;
	cub->player.player_speed = PLYSPEED;
	cub->player.player_rot_speed = PLYROTSPEED;
	cub->player.pos.color = VERDE;
	cub->player.move = STOP;
	cub->player.rotate = STOP;
	cub->fov = FOV;
	cub->map.max_x = 0;
	cub->map.max_y = 0;
	return (EXIT_SUCCESS);
}
