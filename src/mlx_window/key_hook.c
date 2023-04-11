#include "defines.h"
#include "mlx.h"
#include "time.h"
#include "draw.h"
#include <sys/time.h>


int	terminate_program(void *param);

/* 
*	This function handle when a key is pressed
*/

int	key_press(int key, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (key == KEY_ESC)
		terminate_program(cub);	
	if (key == KEY_C)
		clear_screen(&cub->screen);
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
	draw_ray(&cub->screen, cub->test_ray);
	draw_line(&cub->screen, cub->walls[0].p1, cub->walls[0].p2);
	mlx_put_image_to_window(cub->screen.handler,cub->screen.win, \
	cub->screen.img, 0, 0);
	num_frames++;
	return (EXIT_SUCCESS);
}
