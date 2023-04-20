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

bool	window_init(t_cub *cub)
{
	cub->screen.handler = mlx_init();
	if (!cub->screen.handler)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	cub->screen.win = mlx_new_window(cub->screen.handler, WINX, WINY, "Cube3D");
	if (!cub->screen.win)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	cub->screen.img = mlx_new_image(cub->screen.handler, WINX, WINY);
	if (!cub->screen.img)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	cub->screen.img_buff = mlx_get_data_addr(cub->screen.img,
			NULL, NULL, NULL);
	return (0);
}