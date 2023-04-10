#include "defines.h"

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_cub	*cub;

	(void) key;
	cub = (t_cub *)param;
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
