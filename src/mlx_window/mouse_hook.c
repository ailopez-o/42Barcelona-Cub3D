#include "defines.h"
#include "draw.h"


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
	//printf("[%d][%d]\n", x, y);
	return (EXIT_SUCCESS);
}

/* 
*	This function handle every time mouse moved
*/

int	mouse_move(int x, int y, void *param)
{
	t_cub	*cub;

	(void)x;
	(void)y;
	cub = (t_cub *)param;
	cub->test_ray.dir[X] =  x - cub->test_ray.pos.x;
	cub->test_ray.dir[Y] =  cub->test_ray.pos.y - y;
	draw_ray(&cub->screen, cub->test_ray);
	return (EXIT_SUCCESS);
}

