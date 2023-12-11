/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_letters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:02:53 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/11 13:02:13 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

bool	is_valid_character(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

int	validate_map_line(char *line)
{
	static int	player_direction_count = 0;
	int			i;

	i = 0;
	while (line && line[i])
	{
		if (!is_valid_character(line[i]))
		{
			error("Invalid character in the map\n");
			exit(0);
		}
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
			player_direction_count++;
		i++;
	}
	return (player_direction_count);
}
