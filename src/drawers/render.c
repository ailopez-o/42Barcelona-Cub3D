#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3D(t_mlx *screen, t_player play, t_colision *colision);

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
	draw_player(&cub->screen, cub->player, MINIMAPSCALE);
	draw_objets(&cub->screen, cub->map.objets, MINIMAPSCALE);
	render_3D(&cub->screen, cub->player, cub->player.ray_colider);
	//draw_ray_collider(cub, &cub->screen, cub->player.pos, cub->player.ray_colider);
	mlx_put_image_to_window(cub->screen.handler,cub->screen.win, \
	cub->screen.img, 0, 0);
	num_frames++;
	return (EXIT_SUCCESS);
}

void	draw_player(t_mlx *screen, t_player player, float scale)
{
	t_point	scaled_pos;

	scaled_pos = player.pos;
	scaled_pos.x *= scale;
	scaled_pos.y *= scale;
	draw_circle(screen, scaled_pos, 5, VERDE);
	draw_vector(screen, player.front, scaled_pos, VERDE);
	draw_vector(screen, player.cam, scaled_pos, ROJO);
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
		start.x = WINX - iter;
		start.y = (-line_height / 2 + WINY / 2);
		start.color = color_fade(WALLCOLOR, colision->distance);
		if (is_horizontal(colision->line))
			start.color = color_fade(DARKWALL, colision->distance);
		end.x = WINX - iter;
		end.y = (line_height / 2 + WINY / 2);
		if (colision->distance > PLYVIEW)
			end.y = WINY;
		end.color = start.color;
		draw_line(screen, start, end);
		if (end.y < WINY)
		{
			start.y = end.y;
			end.y = WINY;
			start.color = SKYCOLOR;
			end.color = SKYCOLOR;
			draw_line(screen, start, end);
		}
		colision++;
		iter++;
	}
}

void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions)
{
	static int	iter = 0;

	while (colisions->valid)
	{
		pos.color = WHITE;
		colisions->point.color = WALLCOLOR;
		draw_line(screen, pos, colisions->point);
		colisions++;
		iter++;
		if (iter > WIN2D)
			iter = 0;
	}

}

void draw_objets(t_mlx *screen, t_objet *objets, float scale)
{
	while(objets->type == WALL)
	{
		draw_polygon(screen, objets->polygon, scale);
		objets++;
	}
}
