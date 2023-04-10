#include "defines.h"

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
	(void) x;
	(void) y;
	cub = (t_cub *)param;
	return (EXIT_SUCCESS);
}

/* 
*	This function handle every time mouse moved
*/

int	mouse_move(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void) button;
	(void) x;
	(void) y;
	cub = (t_cub *)param;
	return (EXIT_SUCCESS);
}

