/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:47:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/29 15:47:59 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	init_cub(t_cub *cub);
bool	window_init(t_mlx *screen);
bool	parse_map(int argv, char **argc, t_cub *cub);
bool	executor(t_cub *cub);
