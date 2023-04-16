#include "defines.h"
#include "mlx.h"
#include "time.h"
#include "draw.h"
#include "vectors.h"
#include "raycast.h"
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
		cub->player.front = rotate_vector(cub->player.front, 10);
	if (key == KEY_RIGHT)
		cub->player.front = rotate_vector(cub->player.front, -10);
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

int	render(void *param)
{
	t_cub					*cub;
	static int				num_frames = 0;
	static unsigned long	last_time = 0;
	unsigned long			current_time;
	struct timeval			time;
	t_point					polygon[4];

	cub = (t_cub *)param;
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000);
	if (current_time != last_time)
	{
		last_time = (time.tv_sec * 1000);
		ft_putstr_fd("\rFPS >> ", 1);
		ft_putnbr_fd(num_frames, 1);
		num_frames = 0;
	}
	clear_screen(&cub->screen);
	//free(cub->player.ray_colider);
	cub->player.ray_colider = get_dir_ray_collider(cub->player.pos, cub->player.cam, 60, cub->objets);
	draw_player(&cub->screen, cub->player);
	draw_objets(&cub->screen, cub->objets);
	draw_ray_collider(&cub->screen, cub->player.pos, cub->player.ray_colider);
	mlx_put_image_to_window(cub->screen.handler,cub->screen.win, \
	cub->screen.img, 0, 0);
	num_frames++;
	return (EXIT_SUCCESS);
}
