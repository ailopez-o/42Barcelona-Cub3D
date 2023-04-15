	
#include "defines.h"
#include "hooks.h"
#include "mlx.h"
#include "draw.h"

void hardcoder(t_cub *cub);

int	main(int argv, char **argc)
{
	t_cub		cub;
	t_line		wall;
	t_point		ray_position;

	cub.screen.handler = mlx_init();
	cub.screen.win = mlx_new_window(cub.screen.handler, WINX, WINY, \
	"Cube3D");
	cub.screen.img = mlx_new_image(cub.screen.handler, WINX, WINY);
	cub.screen.img_buff = mlx_get_data_addr(cub.screen.img, \
		&cub.screen.bitxpixel, &cub.screen.lines, &cub.screen.endian);

	hardcoder(&cub);

	mlx_hook(cub.screen.win, 2, 0, key_press, &cub);
	mlx_hook(cub.screen.win, 3, 0, key_release, &cub);
	mlx_hook(cub.screen.win, 4, 0, mouse_press, &cub);
	mlx_hook(cub.screen.win, 5, 0, mouse_release, &cub);
	mlx_hook(cub.screen.win, 6, 0, mouse_move, &cub);
	mlx_hook(cub.screen.win, 17, 0, terminate_program, &cub);
	mlx_loop_hook(cub.screen.handler, render, &cub);
	mlx_loop(cub.screen.handler);
}


void hardcoder(t_cub *cub)
{
	cub->objets = ft_calloc (sizeof(t_objet), 10);

	cub->objets[0].type = WALL;
	cub->objets[0].polygon.color = SUPERAZUL;
	cub->objets[0].polygon.p1.x = 800;
	cub->objets[0].polygon.p1.y = 100;
	cub->objets[0].polygon.p2.x = 800;
	cub->objets[0].polygon.p2.y = 600;
	cub->objets[0].polygon.p3.x = 900;
	cub->objets[0].polygon.p3.y = 600;
	cub->objets[0].polygon.p4.x = 900;
	cub->objets[0].polygon.p4.y = 100;

	cub->objets[1].type = WALL;
	cub->objets[1].polygon.color = SUPERAZUL;
	cub->objets[1].polygon.p1.x = 20;
	cub->objets[1].polygon.p1.y = 300;
	cub->objets[1].polygon.p2.x = 600;
	cub->objets[1].polygon.p2.y = 100;
	cub->objets[1].polygon.p3.x = 620;
	cub->objets[1].polygon.p3.y = 700;
	cub->objets[1].polygon.p4.x = 40;
	cub->objets[1].polygon.p4.y = 400;





	cub->walls = malloc(sizeof (t_line) * 20);
	cub->walls[0].p1.x = 800;
	cub->walls[0].p1.y = 100;
	cub->walls[0].p1.color = ROJO;
	cub->walls[0].p2.x = 800;
	cub->walls[0].p2.y = 600;
	cub->walls[0].p2.color = ROJO;
	cub->walls[1].p1.x = 900;
	cub->walls[1].p1.y = 100;
	cub->walls[1].p1.color = ROJO;
	cub->walls[1].p2.x = 900;
	cub->walls[1].p2.y = 600;
	cub->walls[1].p2.color = ROJO;
	cub->walls[2].p1.x = 0;
	cub->walls[2].p1.y = 0;
	cub->walls[2].p2.x = WINX;
	cub->walls[2].p2.y = 0;
	cub->walls[3].p1.x = 0;
	cub->walls[3].p1.y = 0;
	cub->walls[3].p2.x = 0;
	cub->walls[3].p2.y = WINY;
	cub->walls[4].p1.x = 0;
	cub->walls[4].p1.y = WINY;
	cub->walls[4].p2.x = WINX;
	cub->walls[4].p2.y = WINY;
	cub->walls[5].p1.x = WINX;
	cub->walls[5].p1.y = WINY;
	cub->walls[5].p2.x = WINX;
	cub->walls[6].p2.y = 100;
	cub->walls[6].p1.x = 20;
	cub->walls[6].p1.y = 300;
	cub->walls[6].p2.x = 600;
	cub->walls[7].p1.x = -1;


	cub->player.pos.x = 100;
	cub->player.pos.y = 400;
	cub->player.pos.color = VERDE;
	cub->player.front.dir[X] = 0;
	cub->player.front.dir[Y] = 1;
	cub->player.cam.dir[X] = 0;
	cub->player.cam.dir[Y] = 1;
}