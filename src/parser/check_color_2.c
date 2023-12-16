/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:41:07 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/12 12:42:31 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool		validate_map(char *path, t_cub *cub);
int			get_int_array(char *line);
int			get_data_type(char *line);
int			add_texture(char *path, t_texture *textures, t_mlx *screen,
				int type);
int			color_parser(char *line);
int			check_map(t_map *map);
int			map_builder(char **int_map, int scale, t_map *map,
				t_player *player);
int			**resize_matrix(int **matrix, int *width, int *height);
int			**get_image_matrix(char *data, int width, int height);
t_texture	*get_texture(t_texture *textures, int type);
bool		valid_map_from_player(t_data *data);

void	remove_spaces_within_numbers(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

bool	is_valid_color(char *str)
{
	int	commas;
	int	nums;
	int	i;

	commas = 0;
	nums = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			commas++;
		else if (str[i] >= '0' && str[i] <= '9')
			nums++;
		else
			return (false);
		i++;
	}
	return (commas == 2 && nums > 0);
}

bool	is_within_range(int num)
{
	return (num >= 0 && num <= 255);
}

void	free_memory(char *trim_line, char **splitted)
{
	free(trim_line);
	free(splitted[0]);
	free(splitted[1]);
	free(splitted[2]);
	free(splitted);
}

int	color_parser(char *line)
{
	char	*trim_line;
	char	**splitted;
	int		color[3];
	int		hex;

	trim_line = ft_str_trim(line + 1);
	remove_spaces_within_numbers(trim_line);
	splitted = ft_split(trim_line, ',');
	if (is_valid_color(trim_line) && splitted && splitted[0] && splitted[1]
		&& splitted[2])
	{
		color[0] = ft_atoi(splitted[0]);
		color[1] = ft_atoi(splitted[1]);
		color[2] = ft_atoi(splitted[2]);
		if (is_within_range(color[0]) && is_within_range(color[1])
			&& is_within_range(color[2]))
		{
			hex = color[0] << 16 | color[1] << 8 | color[2];
			free_memory(trim_line, splitted);
			return (hex);
		}
	}
	free_memory(trim_line, splitted);
	return (-1);
}
