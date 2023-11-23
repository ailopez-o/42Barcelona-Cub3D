/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:36:52 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 18:03:07 by framos-p         ###   ########.fr       */
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
void	render_column(t_cub *cub, float angulo_player, t_colision *colision,
			int iter);
float	calculate_orto_dist(float angulo_player, float angulo_ray,
			t_colision *colision);
float	calculate_line_height(float orto_dist, float fov_dist);
void	initialize_stripe(t_line *stripe, t_colision *colision, int iter,
			float line_height);
void	draw_textures_and_shadow(t_cub *cub, t_line *stripe,
			t_colision *colision, float line_height);
void	render_map(t_cub *cub);
void	render_wall(t_cub *cub, t_objet object);
void	scale_and_draw_line(t_cub *cub, t_line line, int color);
float	determine_scale(float mapwidth, float mapheight);
t_point	scale_position(t_point position, float scale);

/*
 * render - Renders the game on the screen
 * @param: A void pointer to the game structure
 *
 * This function renders the game on the screen using the mlx library.
 * It clears the screen, draws the walls and player, and updates the
 * fps counter.
 *
 * Return: Returns EXIT_SUCCESS on success.
 */

static void	update_frame_string(int num_frames, char **frame_str)
{
	*frame_str = ft_itoa(num_frames);
	*frame_str = ft_strjoin("FPS ", *frame_str);
}

static void	render_frame(t_cub *cub, int *num_frames, unsigned long *last_time,
				char **frame_str)
{
	unsigned long	current_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000);
	if (current_time != *last_time)
	{
		*last_time = (time.tv_sec * 1000);
		ft_putstr_fd("\rFPS ", 1);
		ft_putnbr_fd(*num_frames, 1);
		update_frame_string(*num_frames, frame_str);
		*num_frames = 0;
	}
}

int	render(void *param)
{
	t_cub					*cub;
	static int				num_frames = 0;
	static unsigned long	last_time = 0;
	static char				*frame_str = "null";

	cub = (t_cub *)param;
	render_frame(cub, &num_frames, &last_time, &frame_str);
	cub->fov_dist = (WIN2D / 2) / tan((cub->fov / 2) * (M_PI / 180));
	clear_screen(&cub->screen);
	player_position(cub);
	get_dir_ray_collider(&cub->player, cub->fov, cub->map.objets);
	render_3d(cub);
	render_map(cub);
	mlx_put_image_to_window(cub->screen.handler, cub->screen.win,
		cub->screen.img, 0, 0);
	mlx_string_put(cub->screen.handler, cub->screen.win, 10, 10, ROJO,
		frame_str);
	num_frames++;
	return (EXIT_SUCCESS);
}

void	initialize_stripe(t_line *stripe, t_colision *colision, int iter,
			float line_height)
{
	stripe->p1.x = WINX - iter;
	stripe->p1.y = (-line_height / 2 + WINY / 2);
	stripe->p1.color = color_fade(WALLCOLOR, colision->distance);
	stripe->p2.x = WINX - iter;
	stripe->p2.y = (line_height / 2 + WINY / 2);
	if (colision->distance > PLYVIEW)
		stripe->p2.y = WINY;
	stripe->p2.color = stripe->p1.color;
}

void	draw_textures_and_shadow(t_cub *cub, t_line *stripe,
			t_colision *colision, float line_height)
{
	bool	b_shadow;

	b_shadow = is_horizontal(colision->line);
	draw_texture_line(&cub->screen, *stripe, adjust_column(colision,
			distance_between_points(stripe->p1, stripe->p2)), b_shadow);
	if (stripe->p2.y < WINY)
	{
		stripe->p1.y = stripe->p2.y;
		stripe->p2.y = WINY;
		stripe->p1.color = cub->map.top_color;
		stripe->p2.color = cub->map.top_color;
		draw_line(&cub->screen, stripe->p1, stripe->p2);
	}
}
