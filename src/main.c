	
#include "defines.h"
#include "hooks.h"

int	main(int argv, char **argc)
{
	t_cub	cub;

	mlx_hook(cub.screen.win, 2, 0, key_press, &cub);
	mlx_hook(cub.screen.win, 3, 0, key_release, &cub);
	mlx_hook(cub.screen.win, 4, 0, mouse_press, &cub);
	mlx_hook(cub.screen.win, 5, 0, mouse_release, &cub);
	mlx_hook(cub.screen.win, 6, 0, mouse_move, &cub);
	//mlx_hook(cub.screen.win, 17, 0, terminate_program, &cub);
	mlx_loop(cub.screen.handler);
}