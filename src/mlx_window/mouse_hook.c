#include "defines.h"
#include "draw.h"
#include "vectors.h"



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
	t_cub		*cub;
	t_vector	vector;
	t_point		colision;

	cub = (t_cub *)param;
	vector.dir[X] = x - cub->player.pos.x;
	vector.dir[Y] = WINY - y - cub->player.pos.y;
	cub->player.cam = normalize_vector(vector);
	return (EXIT_SUCCESS);
}

