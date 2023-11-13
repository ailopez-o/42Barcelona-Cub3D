/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:59:40 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/13 20:00:34 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			get_dir_ray_collider(t_player *player, int wide, t_objet *objets);
t_vector	rotate_vector(t_vector vector, float ang);
t_point		go_vector(t_point init, t_vector vector, int steps);
t_point		move_player_vector(t_cub *cub, t_vector vector, int steps);
t_vector	normalize_vector(t_vector vector);
t_line		vector_to_line(t_vector vector, t_point pos, int steps);
t_vector	get_unit_vector(t_point p1, t_point p2);
float		vector_to_angle(t_vector vector);
t_vector	get_geo_vector(char geo);
bool		is_horizontal(t_line line);
bool		is_horizontal(t_line line);
float		angle_between_lines(t_line l1, t_line l2);
double		distance_between_points(t_point p1, t_point p2);
