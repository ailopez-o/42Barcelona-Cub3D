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
	if (load_map(path, &cub->map) != EXIT_SUCCESS)
		return(EXIT_FAILURE);
	cub->player.pos.x = 700;
	cub->player.pos.y = 400;
	cub->player.pos.color = VERDE;
	cub->player.front.dir[X] = 0;
	cub->player.front.dir[Y] = 1;
	cub->player.cam.dir[X] = 0;
	cub->player.cam.dir[Y] = 1;
	return(EXIT_SUCCESS);
	cub->map.objets = ft_calloc (sizeof(t_objet), 10);
	if (!cub->map.objets)
		return (fprintf(stderr, "Cube error: %s\n", strerror(errno)));
	cub->map.objets[0].type = WALL;
	cub->map.objets[0].polygon.color = SUPERAZUL;
	cub->map.objets[0].polygon.p1.x = 800;
	cub->map.objets[0].polygon.p1.y = 100;
	cub->map.objets[0].polygon.p2.x = 800;
	cub->map.objets[0].polygon.p2.y = 600;
	cub->map.objets[0].polygon.p3.x = 900;
	cub->map.objets[0].polygon.p3.y = 600;
	cub->map.objets[0].polygon.p4.x = 900;
	cub->map.objets[0].polygon.p4.y = 100;

	cub->map.objets[1].type = WALL;
	cub->map.objets[1].polygon.color = SUPERAZUL;
	cub->map.objets[1].polygon.p1.x = 20;
	cub->map.objets[1].polygon.p1.y = 300;
	cub->map.objets[1].polygon.p2.x = 600;
	cub->map.objets[1].polygon.p2.y = 100;
	cub->map.objets[1].polygon.p3.x = 620;
	cub->map.objets[1].polygon.p3.y = 700;
	cub->map.objets[1].polygon.p4.x = 40;
	cub->map.objets[1].polygon.p4.y = 700;

	cub->map.objets[2].type = WALL;
	cub->map.objets[2].polygon.color = SUPERAZUL;
	cub->map.objets[2].polygon.p1.x = 1;
	cub->map.objets[2].polygon.p1.y = 1;
	cub->map.objets[2].polygon.p2.x = 1;
	cub->map.objets[2].polygon.p2.y = WINY - 1;
	cub->map.objets[2].polygon.p3.x = WIN2D - 1;
	cub->map.objets[2].polygon.p3.y = WINY - 1;
	cub->map.objets[2].polygon.p4.x = WIN2D - 1;
	cub->map.objets[2].polygon.p4.y = 1;

	cub->player.pos.x = 700;
	cub->player.pos.y = 400;
	cub->player.pos.color = VERDE;
	cub->player.front.dir[X] = 0;
	cub->player.front.dir[Y] = 1;
	cub->player.cam.dir[X] = 0;
	cub->player.cam.dir[Y] = 1;
	return (EXIT_SUCCESS);
}