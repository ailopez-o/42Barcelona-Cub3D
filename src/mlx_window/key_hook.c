#include "defines.h"
#include "mlx.h"


int	terminate_program(void *param);

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_cub	*cub;

	(void) key;
	cub = (t_cub *)param;
	if (key == KEY_ESC)
		terminate_program(cub);	
	return (EXIT_SUCCESS);
}

/* 
*	This function handle when a key is relased
*/

int	key_release(int key, void *param)
{
	t_cub	*cub;

	(void) key;
	cub = (t_cub *)param;
	return (EXIT_SUCCESS);

}


int	terminate_program(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	mlx_destroy_window(cub->screen.handler,cub->screen.win);
	exit(0);
}
