/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:36:52 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/19 17:01:40 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"
#include "drawers.h"
#include "math.h"
#include "geometry.h"
#include <sys/time.h>

void	render_3d(t_cub *cub);
void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos,
			t_colision *colisions);
double	distance_between_points(t_point p1, t_point p2);
int		*adjust_column(t_colision *colision, double distance);
void	player_position(t_cub *cub);
void	render_map(t_cub *cub);

/**
 * render - Renders the game on the screen
 * @param: A void pointer to the game structure
 *
 * This function renders the game on the screen using the mlx library.
 * It clears the screen, draws the walls and player, and updates the
 * fps counter.
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
		ft_putstr_fd("\rFPS ", 1);
		ft_putnbr_fd(num_frames, 1);
		frame_str = ft_itoa(num_frames);
		frame_str = ft_strjoin("FPS ", frame_str);
		num_frames = 0;
	}
	cub->fov_dist = tan((cub->fov / 2) * (M_PI / 180));
	cub->fov_dist = (WIN2D / 2) / tan((cub->fov / 2) * (M_PI / 180));
	clear_screen(&cub->screen);
	player_position(cub);
	get_dir_ray_collider(&cub->player, cub->fov, cub->map.objets);
	render_3d(cub);
	render_map(cub);
	mlx_put_image_to_window(cub->screen.handler, cub->screen.win, \
	cub->screen.img, 0, 0);
	mlx_string_put(cub->screen.handler, cub->screen.win, 10, 10, ROJO,
		frame_str);
	// mlx_string_put(cub->screen.handler,cub->screen.win, 10, 30, ROJO,
	//	ft_strjoin("FOV | ", ft_itoa(cub->fov)));
	// mlx_string_put(cub->screen.handler,cub->screen.win, 10, 50, ROJO,
	//	ft_strjoin("FOV DIST | ", ft_itoa(cub->fov_dist)));
	num_frames++;
	return (EXIT_SUCCESS);
}

void	player_position(t_cub *cub)
{
	t_vector	ortogonal;

	if ((cub->player.move & 0x01) == GO_FRONT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(cub->player.front), cub->player.player_speed);
	if ((cub->player.move & 0x02) == GO_BACK)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, 180)),
				cub->player.player_speed);
	if ((cub->player.move & 0x04) == GO_RIGHT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, -90)),
				cub->player.player_speed);
	if ((cub->player.move & 0x08) == GO_LEFT)
		cub->player.pos = move_player_vector(cub,
				normalize_vector(rotate_vector(cub->player.front, 90)),
				cub->player.player_speed);
	if (cub->player.rotate == ROTATE_R)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front,
					-cub->player.player_rot_speed));
	if (cub->player.rotate == ROTATE_L)
		cub->player.front = normalize_vector(rotate_vector(cub->player.front,
					cub->player.player_rot_speed));
	if (cub->player.rotate)
		cub->player.cam = cub->player.front;
}

void	draw_player(t_mlx *screen, t_player player, float scale)
{
	t_point	scaled_pos;

	scaled_pos = player.pos;
	scaled_pos.x *= scale + 10;
	scaled_pos.y *= scale;
	draw_circle(screen, scaled_pos, 3, VERDE);
}

void	render_3d(t_cub *cub)
{
	t_line		stripe;
	t_vector	vector_ray;
	float		angulo_player;
	float		angulo_ray;
	int			iter;
	float		line_height;
	bool		b_shadow;
	float		orto_dist;
	t_colision	*colision;

	angulo_player = vector_to_angle(cub->player.cam);
	colision = cub->player.ray_colider;
	iter = 0;
	while (colision->valid)
	{
		vector_ray = get_unit_vector(cub->player.pos, colision->point);
		angulo_ray = vector_to_angle(vector_ray);
		///////////////////// PROYECTION PLANE /////////////////////
		orto_dist = colision->distance * cos((angulo_player - angulo_ray)
				* M_PI / 180);
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
		draw_texture_line(&cub->screen, stripe, adjust_column(colision,
				distance_between_points(stripe.p1, stripe.p2)), b_shadow);
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

void	render_map(t_cub *cub)
{
	size_t		iter;
	t_objet		*objects;
	t_polygon	poly;
	int			side;
	float		mapwidth;
	float		mapheight;
	float		scale;
	t_point		scaled_pos;

	mapwidth = cub->map.max_x;
	mapheight = cub->map.max_y;
	if (mapwidth > mapheight)
		scale = (MINIMAPSCALE) / mapwidth;
	else
		scale = (MINIMAPSCALE) / mapheight;
	iter = 0;
	objects = cub->map.objets;
	while (objects[iter].type == WALL)
	{
		side = -1;
		poly = objects[iter].polygon;
		while (++side < 4)
		{
			poly.line[side].p1.color = poly.color;
			poly.line[side].p2.color = poly.color;
			poly.line[side].p1.x = poly.line[side].p1.x * scale + 10;
			poly.line[side].p1.y = poly.line[side].p1.y * scale + 10;
			poly.line[side].p2.x = poly.line[side].p2.x * scale + 10;
			poly.line[side].p2.y = poly.line[side].p2.y * scale + 10;
			draw_line(&(cub->screen), poly.line[side].p1, poly.line[side].p2);
		}
		iter++;
	}
	scaled_pos = cub->player.pos;
	scaled_pos.x = scaled_pos.x * scale + 10;
	scaled_pos.y = scaled_pos.y * scale + 10;
	draw_circle(&(cub->screen), scaled_pos, 3, PLAYER_COLOR);
	draw_ray_collider(cub, &(cub->screen), scaled_pos, cub->player.ray_colider);
}

void	draw_ray_collider(t_cub *cub, t_mlx *screen, t_point pos,
			t_colision *colisions)
{
	int			iter;
	t_point		point;
	float		scale;
	float		mapwidth;
	float		mapheight;

	mapwidth = cub->map.max_x;
	mapheight = cub->map.max_y;
	iter = 0;
	if (mapwidth > mapheight)
		scale = (MINIMAPSCALE) / mapwidth;
	else
		scale = (MINIMAPSCALE) / mapheight;
	while (colisions->valid)
	{
		pos.color = RAY_COLOR_START;
		colisions->point.color = RAY_COLOR_END;
		point = colisions->point;
		point.x = point.x * scale + 10;
		point.y = point.y * scale + 10;
		draw_line(screen, pos, point);
		iter++;
		colisions++;
	}
}

void	draw_objets(t_mlx *screen, t_objet *objets, float scale)
{
	while (objets->type == WALL)
	{
		draw_polygon(screen, objets->polygon, scale);
		objets++;
	}
}
