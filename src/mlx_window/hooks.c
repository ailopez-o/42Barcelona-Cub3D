#include "defines.h"
#include "mlx.h"
#include "events.h"
#include "drawers.h"



/**
 * executor - Sets up and runs the main event loop for the program
 * @cub: A pointer to the main program structure
 *
 * This function sets up the event hooks for key presses, mouse actions,
 * and program termination, and then starts the main event loop.
 */

bool	executor(t_cub *cub)
{
	mlx_hook(cub->screen.win, 2, 0, key_press, cub);
	mlx_hook(cub->screen.win, 3, 0, key_release, cub);
	mlx_hook(cub->screen.win, 4, 0, mouse_press, cub);
	mlx_hook(cub->screen.win, 5, 0, mouse_release, cub);
	mlx_hook(cub->screen.win, 6, 0, mouse_move, cub);
	mlx_hook(cub->screen.win, 17, 0, terminate_program, cub);
	mlx_loop_hook(cub->screen.handler, render, cub);
	mlx_loop(cub->screen.handler);
	return EXIT_SUCCESS;
}
