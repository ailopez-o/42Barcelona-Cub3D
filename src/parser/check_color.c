/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:14:59 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/14 15:11:34 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		line_has_wall(char *line);
int			is_player(char *line);
int			get_int_array(char *line);
int			get_data_type(char *line);
int			add_texture(char *path, t_texture *textures, t_mlx *screen,
				int type);
int			color_parser(char *line);
bool		is_valid_character(char c);
int			validate_map_line(char *line);

int	is_texture_data(int data_type)
{
	return (data_type == NO || data_type == SO || data_type == WE
		|| data_type == EA);
}

int	is_color_data(int data_type)
{
	return (data_type == F || data_type == C);
}

void	handle_texture_data(char *line, t_cub *cub, int data_type)
{
	int	texture_added;

	texture_added = add_texture(line, cub->map.textures,
			&cub->screen, data_type);
	if (texture_added == EXIT_FAILURE)
		error("Failed adding texture\n");
}

int	handle_color_data(char *line, t_cub *cub, int data_type)
{
	int	parsed_color;

	parsed_color = color_parser(line);
	if (parsed_color == -1)
	{
		error("Invalid color format\n");
		return (-1);
	}
	else
	{
		if (data_type == F)
			cub->map.bottom_color = parsed_color;
		else if (data_type == C)
			cub->map.top_color = parsed_color;
	}
	return (EXIT_SUCCESS);
}

int	process_texture_color(char *line, t_cub *cub)
{
	int	data_type;

	data_type = get_data_type(line);
	if (is_texture_data(data_type))
	{
		handle_texture_data(line, cub, data_type);
		//	return (EXIT_FAILURE);
	}
	else if (is_color_data(data_type))
	{
		if (handle_color_data(line, cub, data_type) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
