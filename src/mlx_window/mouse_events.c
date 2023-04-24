#include "defines.h"
#include "drawers.h"
#include "geometry.h"
#include "mlx.h"




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
	t_cub			*cub;
	t_vector		vector;
	static t_point	last_point;
	float			diff;

	cub = (t_cub *)param;
	if (x > WINX || x < 0 || y > WINY || y < 0)
		return (EXIT_SUCCESS);
	diff = x - last_point.x;
	if (diff > 0)
		cub->player.front = rotate_vector(cub->player.front, -2);
	else
		cub->player.front = rotate_vector(cub->player.front, 2);
	cub->player.cam = cub->player.front;
	if (x < WINX/2)
		mlx_mouse_move(cub->screen.win, 3 * (WINX / 4), y);
		

	last_point.x = x;
	last_point.y = y;
	// half_frame = 3 * (WINX / 4); 
	// vector.dir[X] = x - half_frame;
	// vector.dir[Y] = y - WINY/2;
	// vector.dir[X] = x - cub->player.pos.x;
	// vector.dir[Y] = WINY - y - cub->player.pos.y;
	// cub->player.cam = normalize_vector(vector);
	// cub->player.front = normalize_vector(vector);
	return (EXIT_SUCCESS);
}

