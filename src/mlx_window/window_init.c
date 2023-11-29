/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:09:35 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 16:09:54 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include <errno.h>
#include <string.h>

/**
 * window_init - Initializes the window for the game
 * @cub: The main game structure
 *
 * This function initializes the window using the mlx library and sets up
 * the image buffer for the screen.
 *
 * Return: Returns 0 on success, otherwise it returns an error message.
 */

bool	window_init(t_mlx *screen)
{
	screen->handler = mlx_init();
	if (!screen->handler)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	screen->win = mlx_new_window(screen->handler, WINX, WINY, "Cube3D");
	if (!screen->win)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	screen->img = mlx_new_image(screen->handler, WINX, WINY);
	if (!screen->img)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	screen->img_buff = mlx_get_data_addr(screen->img,
			NULL, NULL, NULL);
	return (EXIT_SUCCESS);
}
