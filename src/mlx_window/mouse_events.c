/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:29:22 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 10:30:09 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "drawers.h"
#include "geometry.h"
#include "mlx.h"

/* 
*	This function handle every time a mouse button is relased
*/

int	mouse_release(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void) button;
	(void) x;
	(void) y;
	cub = (t_cub *)param;
	return (EXIT_SUCCESS);
}

/*
*	This function handle every time a mouse button is pressed
*/

int	mouse_press(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void) button;
	cub = (t_cub *)param;
	return (EXIT_SUCCESS);
}

/* 
*	This function handle every time mouse moved
*/

int	mouse_move(int x, int y, void *param)
{
	t_cub			*cub;
	static t_point	last_point;
	float			diff;
	float			step;

	cub = (t_cub *)param;
	// if (x < WINX/2)
	// {
	// 	mlx_mouse_move(cub->screen.win, 3 * (WINX / 4), y);
	// 	last_point.x = 3 * (WINX / 4);
	// 	return(EXIT_SUCCESS);
	// }
	// if (x > WINX)
	// {
	// 	last_point.x = 3 * (WINX / 4);
	// 	mlx_mouse_move(cub->screen.win, 3 * (WINX / 4), y);
	// 	return(EXIT_SUCCESS);
	// }
	diff = last_point.x - x;
	step = diff / 10;
	if (diff > 0)
		cub->player.front = rotate_vector(cub->player.front, step);
	else
		cub->player.front = rotate_vector(cub->player.front, step);
	cub->player.cam = cub->player.front;
	last_point.x = x;
	last_point.y = y;
	return (EXIT_SUCCESS);
}
