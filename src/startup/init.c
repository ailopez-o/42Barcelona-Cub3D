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

bool	init_cub(t_cub *cub, char *path)
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
	if (load_map(path, cub) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	mlx_mouse_hide();
	cub->player.ray_colider = ft_calloc(sizeof(t_colision), (WIN2D + 1));
	return(EXIT_SUCCESS);
}
