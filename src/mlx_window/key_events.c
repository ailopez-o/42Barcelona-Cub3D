#include "defines.h"
#include "mlx.h"
#include "time.h"
#include "drawers.h"
#include "geometry.h"
#include <sys/time.h>


int		terminate_program(void *param);
void	moove_player(t_cub *cub, int key);
void	turn_player(t_cub *cub, int key);

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_cub		*cub;

	cub = (t_cub *)param;
	if (key == KEY_ESC)
		terminate_program(cub);
	if (key == KEY_C)
		clear_screen(&cub->screen);
	if (key == KEY_W || key == KEY_UP || key == KEY_S
		|| key == KEY_DOWN || key == KEY_D || key == KEY_A)
		moove_player(cub, key);
	if (key == KEY_LEFT || key == KEY_RIGHT)
		turn_player(cub, key);
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

