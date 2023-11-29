/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:08:47 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 16:09:27 by framos-p         ###   ########.fr       */
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
