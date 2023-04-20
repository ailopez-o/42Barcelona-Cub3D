#include "defines.h"
#include "mlx.h"
#include "time.h"
#include "drawers.h"
#include "geometry.h"
#include <sys/time.h>


int	terminate_program(void *param);

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_cub		*cub;
	t_vector	ortogonal;

	cub = (t_cub *)param;
	if (key == KEY_ESC)
		terminate_program(cub);	
	if (key == KEY_C)
		clear_screen(&cub->screen);
	if (key == KEY_LEFT)
	{
		cub->player.front = rotate_vector(cub->player.front, 10);
		cub->player.cam = cub->player.front;
	}
	if (key == KEY_RIGHT)
	{
		cub->player.front = rotate_vector(cub->player.front, -10);
		cub->player.cam = cub->player.front;
	}
	if (key == KEY_W || key == KEY_UP)
		cub->player.pos = go_vector(cub->player.pos, cub->player.front, 10);
	if (key == KEY_S || key == KEY_DOWN)
		cub->player.pos = go_vector(cub->player.pos, cub->player.front, -10);
	if (key == KEY_A)
	{
		ortogonal = rotate_vector(cub->player.front, 90);
		cub->player.pos = go_vector(cub->player.pos, ortogonal, 10);
	}
	if (key == KEY_D)
	{
		ortogonal = rotate_vector(cub->player.front, -90);
		cub->player.pos = go_vector(cub->player.pos, ortogonal, 10);
	}
	
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

