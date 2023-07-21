/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:02:19 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/07/19 19:10:01 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "utils.h"
#include "parser.h"
#include "init.h"
#include "mlx.h"
#include <fcntl.h>

int			**empty_map(int width, int height);
bool		validate_map(char *path, t_cub *cub);
char		*get_int_array(char *line);
int			get_data_type(char *line);
int			add_texture(char *path, t_texture *textures, t_mlx *screen, int type);
int			color_parser(char *line);
int 		check_map(t_map *map);
int			map_builder(char **int_map, int scale, t_map *map, t_player *player);
int 		**resize_matrix(int **matrix, int *width);
int			**get_image_matrix(char *data, int width, int height);
t_texture	*get_texture(t_texture *textures, int type);




bool	parse_map(int argv, char **argc, char **map, t_cub *cub)
{
	if (argv != 2)
		return EXIT_FAILURE;
	if (ft_strlen(argc[1]) < 4
		|| ft_strncmp(argc[1] + (ft_strlen(argc[1]) - 4), ".cub", 5))
		return EXIT_FAILURE;
	if (validate_map(argc[1], cub))
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}


bool	validate_map(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	char	**map;
	int		num_line;
	int		num_textures;
	int		data_type;

	init_cub(cub);	

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map = malloc(sizeof(char **));
	num_line = 0;
	num_textures = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' ' || line[0] == '\t'))
		{
			cub->map.max_y += 1;
			if (ft_strlen(line) > cub->map.max_x)
				cub->map.max_x = ft_strlen(line);
			map[num_line++] = get_int_array(line);
			map = ft_realloc(map, sizeof(char **) * (num_line + 1));
		}
		else
		{
			data_type = get_data_type(line);
			if (data_type == NO || data_type == SO || data_type == WE || data_type == EA)
			{
				if (add_texture(line, cub->map.textures, &cub->screen, data_type) == EXIT_FAILURE)
				{
					free(line);
					return (EXIT_FAILURE);
				}
			}
			if (data_type == F)
				cub->map.bottom_color = color_parser(line);
			if (data_type == C)
				cub->map.top_color = color_parser(line);
			free(line);
		}
		line = get_next_line(fd);
	}
	printf("size: %d %d\n", cub->map.max_x, cub->map.max_y);
	map[num_line] = NULL;
	if (check_map(&cub->map))
		return(EXIT_FAILURE);
	map_builder(map, MAPSCALE, &cub->map, &cub->player);
	return(EXIT_SUCCESS);
}


bool	valid_map_from_player(int x, int y, char map[11][8], int max_height, int max_width)
{
	int 			its = 0;
	static int		**checker = NULL;
	
	if (checker == NULL)
		checker = empty_map(max_width, max_height);	

	if (checker[y][x] == '1')
		return 0;
	checker[y][x] = '1';
	if (map[y][x] == '1')
		return 0;
	if (x > 0)
		its += valid_map_from_player(x - 1, y, map, max_height, max_width);
	if (x < max_width)
		its += valid_map_from_player(x + 1, y, map,  max_height, max_width);
	if (y > 0)
		its += valid_map_from_player(x, y - 1, map,  max_height, max_width);
	if (y < max_height)
		its += valid_map_from_player(x, y + 1, map,  max_height, max_width);
	if ((x == 0 || x == max_width) && map[y][x] == '0')
		return 1;
	if ((y == 0 || y == max_height) && map[y][x] == '0')
		return 1;
	if (its)
		return 1;
	return 0;
}


int		**empty_map(int width, int height)
{
   	int i;
	int j;
    int	**array;
	
	array = (int**)malloc(height * sizeof(int*));
    if(array == NULL) 
        return NULL;

	i = -1;
	while (i++ < height)
	{
        array[i] = (int*)malloc(width * sizeof(int));
        if(array[i] == NULL) 
		{
			j = -1;
			while (j++ < i)
                free(array[j]);
            free(array);
            return NULL;
        }
    }
    return array;
}


char	*get_int_array(char *line)
{
	char	*char_line;
	int		num_col;

	char_line = ft_calloc(sizeof(char), ft_strlen(line) + 1);

	num_col = 0;
	while(line[num_col])
	{
		if (line[num_col] == '1')
			char_line[num_col] = '1';
		else if (line[num_col] == 'N')
			char_line[num_col] = 'N';
		else if (line[num_col] == 'S')
			char_line[num_col] = 'S';
		else if (line[num_col] == 'E')
			char_line[num_col] = 'E';
		else if (line[num_col] == 'W')
			char_line[num_col] = 'W';
		else
			char_line[num_col] = '0';
		num_col++;
	}
	return (char_line);
}

int	get_data_type(char *line)
{
	if (line[0] && line[0] == 'N' && line[1] && line[1] == 'O' && line[2] && line[2] == ' ')
		return (NO);
	if (line[0] && line[0] == 'S' && line[1] && line[1] == 'O' && line[2] && line[2] == ' ')
		return (SO);
	if (line[0] && line[0] == 'W' && line[1] && line[1] == 'E' && line[2] && line[2] == ' ')
		return (WE);
	if (line[0] && line[0] == 'E' && line[1] && line[1] == 'A' && line[2] && line[2] == ' ')
		return (EA);
	if (line[0] && line[0] == 'S' && line[1] && line[1] == 'C' && line[2] && line[2] == ' ')
		return (SC);
	if (line[0] && line[0] == 'C' && line[1] && line[1] == ' ')
		return (C);
	if (line[0] && line[0] == 'F' && line[1] && line[1] == ' ')
		return (F);
	return (0);
}

int	add_texture(char *path, t_texture *textures, t_mlx *screen, int type)
{
	char	*str_trimed;

	while(textures->valid == true)
		textures++;
	str_trimed = ft_str_trim(path + 3);
	textures->path = ft_substr(str_trimed, 0, ft_strlen(path) - 1);
	free (str_trimed);
	textures->img.ptr = mlx_xpm_file_to_image(screen->handler, textures->path, &textures->width, &textures->height);
	if (textures->img.ptr == NULL)
		return (EXIT_FAILURE);
	textures->img.addr = mlx_get_data_addr(textures->img.ptr, NULL, NULL, NULL);
	if (textures->img.addr == NULL)
		return (EXIT_FAILURE);
	textures->valid = true;
	textures->type = type;
	textures->img.matrix = resize_matrix(get_image_matrix(textures->img.addr, textures->width, textures->height), &textures->width);
	return (EXIT_SUCCESS);
	//Mirar si hace falta realloc
}

int	color_parser(char *line)
{
	char	*trim_line;
	char	**splitted;
	int		color[3];
	int		hex;

	trim_line = ft_str_trim(line + 1);
	splitted = ft_split(trim_line, ',');
	color[0] = ft_atoi(splitted[0]);
	color[1] = ft_atoi(splitted[1]);
	color[2] = ft_atoi(splitted[2]);
	hex = color[0] << 16 | color[1] << 8 | color[2];
	free(trim_line);
	free (splitted[0]);
	free (splitted[1]);
	free (splitted[2]);
	free (splitted);
	return (hex);
}

int check_map(t_map *map)
{

	if (!get_texture(map->textures, NO))
		return(EXIT_FAILURE);
	if (!get_texture(map->textures, SO))
		return(EXIT_FAILURE);
	if (!get_texture(map->textures, WE))
		return(EXIT_FAILURE);
	if (!get_texture(map->textures, EA))
		return(EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

