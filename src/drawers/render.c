#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3D(t_mlx *screen, t_player play, t_colision *colision);
void 	draw_objets(t_mlx *screen, t_objet *objets);
void	draw_player(t_mlx *screen, t_player player);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions);

/**
 * render - Renders the game on the screen
 * @param: A void pointer to the game structure
 *
 * This function renders the game on the screen using the mlx library.
 * It clears the screen, draws the walls and player, and updates the fps counter.
 *
 * Return: Returns EXIT_SUCCESS on success.
 */

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
	cub->player.ray_colider = get_dir_ray_collider(cub->player.pos, cub->player.cam, FOV, cub->map.objets);
	draw_player(&cub->screen, cub->player);
	draw_objets(&cub->screen, cub->map.objets);
	render_3D(&cub->screen, cub->player, cub->player.ray_colider);
	draw_ray_collider(cub, &cub->screen, cub->player.pos, cub->player.ray_colider);
	mlx_put_image_to_window(cub->screen.handler,cub->screen.win, \
	cub->screen.img, 0, 0);
	num_frames++;
	return (EXIT_SUCCESS);
}

void	draw_player(t_mlx *screen, t_player player)
{
	draw_circle(screen, player.pos, 5, VERDE);
	draw_vector(screen, player.front, player.pos, VERDE);
	draw_vector(screen, player.cam, player.pos, ROJO);
}


void	render_3D(t_mlx *screen, t_player play, t_colision *colision)
{
	t_point		start;
	t_point		end;
	t_vector	vector_ray;
	t_vector	vector_playr = play.front;
	float		angulo_player = vector_to_angle(play.front);
	float		angulo_ray;
	int			iter;
	int			line_height;

	iter = 0;
	while (colision->valid)
	{
		vector_ray = get_unit_vector(play.pos, colision->point),
		angulo_ray = vector_to_angle(vector_ray);
		line_height = (int)(WINY / (colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) * 100);
		// if (iter == 0)
		// 	printf("\rangulo ply: %f, ang ray %f, diferencia %f, lo que necesitamos : a = cos(ß) * h = %f * %f = %f", angulo_player, angulo_ray, angulo_player - angulo_ray, cos((angulo_player - angulo_ray) * M_PI / 180), colision->distance, cos((angulo_player - angulo_ray) * M_PI / 180) * colision->distance);
		start.x = WINX - iter;
		start.y = (-line_height / 2 + WINY / 2);
		// start.y = WINY / 2 - ((colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) / 2);
		start.color = color_fade(0xE83535, colision->distance);
		end.x = WINX - iter;
		end.y = (line_height / 2 + WINY / 2);
		// end.y = WINY / 2 + ((colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180)) / 2);
		if (colision->distance > 900)
			end.y = WINY;
		end.color = color_fade(0xE83535, colision->distance);
		draw_line(screen, start, end);
		colision++;
		iter++;
		// if (iter > WIN2D)
		// 	iter = 0;
	}
}



void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions)
{
	static int	iter = 0;

	while (colisions->valid)
	{
		pos.color = WHITE;
		colisions->point.color = ROJO;
		draw_line(screen, pos, colisions->point);
		colisions++;
		iter++;
		if (iter > WIN2D)
			iter = 0;
	}

}

void draw_objets(t_mlx *screen, t_objet *objets)
{
	while(objets->type == WALL)
	{
		draw_polygon(screen, &objets->polygon);
		objets++;
	}
}