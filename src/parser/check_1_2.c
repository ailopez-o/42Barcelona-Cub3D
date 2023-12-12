/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:36:39 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/12 12:21:06 by framos-p         ###   ########.fr       */
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
void		process_texture_color(char *line, t_cub *cub);

void	process_map(char *line, t_cub *cub, char ***map, t_pars *pars)
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
			cub->player.matrix_pos.y = pars->num_line + 1;
			cub->player.init_view = line[(int)cub->player.matrix_pos.x];
		}
		if (get_int_array(line) == EXIT_FAILURE)
			error("Forbidden item inside map\n");
		if (validate_map_line(line) > 1)
		{
			error("More than one player in the map\n");
			exit(0);
		}
		(*map)[pars->num_line] = ft_strdup(line);
		(pars->num_line)++;
		*map = ft_realloc(*map, sizeof(char **) * (pars->num_line + 1));
	}
}

void	process_map_line(char *line, t_cub *cub, char ***map, t_pars *pars)
{
	if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' '))
		process_map(line, cub, map, pars);
	else
		if (pars->map_parsing == true)
			return ;
	process_texture_color(line, cub);
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

void	parse_map_file(int fd, t_cub *cub, char ***map, t_pars *pars)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		process_map_line(line, cub, map, pars);
		line = get_next_line(fd);
	}
	if (validate_map_line(line) != 1)
	{
		error("No player in he map\n");
		exit(0);
	}
}
