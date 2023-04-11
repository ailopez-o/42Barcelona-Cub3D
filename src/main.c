	
#include "defines.h"
#include "hooks.h"
#include "mlx.h"
#include "draw.h"

int	main(int argv, char **argc)
{
	t_cub	cub;

	cub.screen.handler = mlx_init();
	cub.screen.win = mlx_new_window(cub.screen.handler, WINX, WINY, \
	"Cube3D");
	cub.screen.img = mlx_new_image(cub.screen.handler, WINX, WINY);
	cub.screen.img_buff = mlx_get_data_addr(cub.screen.img, \
		&cub.screen.bitxpixel, &cub.screen.lines, &cub.screen.endian);

	mlx_hook(cub.screen.win, 2, 0, key_press, &cub);
	mlx_hook(cub.screen.win, 3, 0, key_release, &cub);
	mlx_hook(cub.screen.win, 4, 0, mouse_press, &cub);
	mlx_hook(cub.screen.win, 5, 0, mouse_release, &cub);
	mlx_hook(cub.screen.win, 6, 0, mouse_move, &cub);
	mlx_hook(cub.screen.win, 17, 0, terminate_program, &cub);
	mlx_loop_hook(cub.screen.handler, render, &cub);
	mlx_loop(cub.screen.handler);
}