/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:36:39 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/18 19:02:01 by framos-p         ###   ########.fr       */
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
int			process_texture_color(char *line, t_cub *cub);

int	process_map(char *line, t_cub *cub, char ***map, t_pars *pars)
{
	int	data_type;

	if (pars->map_parsing == true || line_has_wall(line) == true)
	{
		pars->map_parsing = true;
		cub->map.max_y += 1;
		if (ft_strlen(line) > cub->map.max_x)
			cub->map.max_x = ft_strlen(line);
		if (is_player(line))
		{
			cub->player.matrix_pos.x = is_player(line);
			cub->player.matrix_pos.y = pars->num_line;
			cub->player.init_view = line[(int)cub->player.matrix_pos.x];
		}
		if (get_int_array(line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		(*map)[pars->num_line] = ft_strdup(line);
		(pars->num_line)++;
		*map = ft_realloc(*map, sizeof(char **) * (pars->num_line + 1));
		if (*map == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_map_line(char *line, t_cub *cub, char ***map, t_pars *pars)
{
	if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' '))
	{
		if (process_map(line, cub, map, pars) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		if (pars->map_parsing == true)
			return (EXIT_SUCCESS);
	if (process_texture_color(line, cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	open_map_file(char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
	{
		error("Failed opening map\n");
		return (false);
	}
	return (true);
}

int	parse_map_file(int fd, t_cub *cub, char ***map, t_pars *pars)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line(line, cub, map, pars) == EXIT_FAILURE)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (validate_map_line(NULL) != 1)
		return (error("No player in the map\n"));
	return (EXIT_SUCCESS);
}
