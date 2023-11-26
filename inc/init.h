/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:03:31 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/07/19 19:11:05 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	init_cub(t_cub *cub);
bool	window_init(t_mlx *screen);
bool	parse_map(int argv, char **argc, t_cub *cub);
bool	executor(t_cub *cub);