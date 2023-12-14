/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:47:55 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/14 15:33:04 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	init_cub(t_cub *cub);
bool	window_init(t_mlx *screen);
int 	parse_map(int argv, char **argc, t_cub *cub);
bool	executor(t_cub *cub);
