/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:17:17 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:17:41 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	my_pixel_put(t_mlx *screen, t_point pixel);
void	draw_line(t_mlx *screen, t_point start, t_point end);
void	draw_vector(t_mlx *screen, t_vector vector, t_point pos, int color);
void	clear_screen(t_mlx *screen);
void	draw_player(t_mlx *screen, t_player player, float scale);
void	draw_circle(t_mlx *screen, t_point center, int radius, int color);
void	draw_polygon(t_mlx *screen, t_polygon polygon, float scale);
void	draw_objets(t_mlx *screen, t_objet *objets, float scale);
int		render(void *param);
int		gradient(int startcolor, int endcolor, int len, int pix);
int		color_fade(int color_hex, int value);
void	draw_texture_line(t_mlx *screen, t_line stripe, int *column,
			bool b_shadow);
