#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "math.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3D(t_cub *cub);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions);
double	distance_between_points(t_point p1, t_point p2);
int		*adjust_column(t_colision *colision, double distance);
void	player_position(t_cub *cub);

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
	static char				*frame_str = "null";

	cub = (t_cub *)param;
	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000);
	if (current_time != last_time)
	{
		last_time = (time.tv_sec * 1000);
		ft_putstr_fd("\rFPS | ", 1);
		ft_putnbr_fd(num_frames, 1);
		frame_str = ft_itoa(num_frames);
		frame_str = ft_strjoin(frame_str, " FPS ");
		num_frames = 0;
	}
	cub->fov_dist = tan((cub->fov / 2) * (M_PI / 180));
	cub->fov_dist =(WIN2D / 2) / tan((cub->fov / 2) * (M_PI / 180));
	clear_screen(&cub->screen);
	player_position(cub);
	get_dir_ray_collider(&cub->player, cub->fov, cub->map.objets);
	draw_player(&cub->screen, cub->player, MINIMAPSCALE);
	draw_ray_collider(cub, &cub->screen, cub->player.pos, cub->player.ray_colider);
	draw_objets(&cub->screen, cub->map.objets, MINIMAPSCALE);
	render_3D(cub);
	mlx_put_image_to_window(cub->screen.handler,cub->screen.win, \
	cub->screen.img, 0, 0);
	mlx_string_put(cub->screen.handler,cub->screen.win, 100, 100, ROJO, frame_str);
	mlx_string_put(cub->screen.handler,cub->screen.win, 200, 100, ROJO, ft_strjoin("FOV | ", ft_itoa(cub->fov)));
	mlx_string_put(cub->screen.handler,cub->screen.win, 100, 200, ROJO, ft_strjoin("FOV DIST | ", ft_itoa(cub->fov_dist)));
	num_frames++;

	return (EXIT_SUCCESS);
}

void	player_position(t_cub *cub)
{
	t_vector	ortogonal;

	if ((cub->player.move & 0x01) == GO_FRONT)
		cub->player.pos = move_player_vector(cub, normalize_vector(cub->player.front), cub->player.player_speed);
	if ((cub->player.move & 0x02) == GO_BACK)
		cub->player.pos = move_player_vector(cub, normalize_vector(rotate_vector(cub->player.front, 180)), cub->player.player_speed);
	if ((cub->player.move & 0x04) == GO_RIGHT)
		cub->player.pos = move_player_vector(cub, normalize_vector(rotate_vector(cub->player.front, -90)), cub->player.player_speed);
	if ((cub->player.move & 0x08) == GO_LEFT)
		cub->player.pos = move_player_vector(cub, normalize_vector(rotate_vector(cub->player.front, 90)), cub->player.player_speed);
	if (cub->player.rotate == ROTATE_R)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front, -cub->player.player_rot_speed));
	if (cub->player.rotate == ROTATE_L)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front, cub->player.player_rot_speed));
	if (cub->player.rotate)
		cub->player.cam = cub->player.front;
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


void	render_3D(t_cub *cub)
{
	t_line		stripe;
	t_vector	vector_ray;
	float		angulo_player = vector_to_angle(cub->player.cam);
	float		angulo_ray;
	int			iter;
	float		line_height;
	bool		b_shadow;
	float		orto_dist;
	t_colision	*colision;

	colision = cub->player.ray_colider;
	iter = 0;
	while (colision->valid)
	{
		vector_ray = get_unit_vector(cub->player.pos, colision->point),
		angulo_ray = vector_to_angle(vector_ray);
		//orto_dist = colision->distance * cos((angulo_player - angulo_ray) * M_PI / 180);
		//line_height = (int) (MAPSCALE * (WINY / orto_dist));

		///////////////////// PROYECTION PLANE /////////////////////
		orto_dist = colision->distance  * cos((angulo_player - angulo_ray) * M_PI / 180);
		line_height = (int)((MAPSCALE / orto_dist) * cub->fov_dist);
		///////////////////////////////////////////

		stripe.p1.x = WINX - iter;
		stripe.p1.y = (-line_height / 2 + WINY / 2);
		stripe.p1.color = color_fade(WALLCOLOR, colision->distance);
		b_shadow = 0;
		if (is_horizontal(colision->line))
			b_shadow = 1;
		stripe.p2.x = WINX - iter;
		stripe.p2.y = (line_height / 2 + WINY / 2);
		if (colision->distance > PLYVIEW)
			stripe.p2.y = WINY;
		stripe.p2.color = stripe.p1.color;
		draw_texture_line(&cub->screen, stripe, adjust_column(colision, distance_between_points(stripe.p1, stripe.p2)), b_shadow);
		if (stripe.p2.y < WINY)
		{
			stripe.p1.y = stripe.p2.y;
			stripe.p2.y = WINY;
			stripe.p1.color = cub->map.top_color;
			stripe.p2.color = cub->map.top_color;
			draw_line(&cub->screen, stripe.p1, stripe.p2);
		}
		colision++;
		iter++;
	}
}

void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos, t_colision *colisions)
{
	int	iter = 0;
	t_point		point;

	pos.x *= MINIMAPSCALE;
	pos.y *= MINIMAPSCALE;
	while (colisions->valid)
	{
		pos.color = WHITE;
		colisions->point.color = WALLCOLOR;
		point = colisions->point;
		point.x *= MINIMAPSCALE;
		point.y *= MINIMAPSCALE;
		//if (iter % 50 == 0)
		draw_line(screen, pos, point);
		iter++;
		colisions++;
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
