
#include "defines.h"
#include "utils.h"
#include "mlx.h"
#include "geometry.h"
#include "parser.h"
#include <fcntl.h>

void	*ft_realloc(void *ptr, size_t size);
int		*get_int_array(char *line);
int		map_builder(int **int_map, int scale, t_map *map, t_player *player);
int		**get_image_matrix(char *data, int width, int height);
void	matrix_printer(int **matrix, int width, int height);
int		get_data_type(char *line);
int		add_texture(char *path, t_texture *textures, t_mlx *screen, int type);
void	print_map_resume(t_map *map);
int		color_parser(char *line);

int	load_map(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	int		**int_map;
	int		num_line;
	int		num_textures;
	int		data_type;

	cub->map.objets = ft_calloc(1, sizeof(t_objet) * 300);
	cub->map.textures = ft_calloc(1, sizeof(t_texture) * 100);

	/////////////////// HARDCODER
	path = ft_strdup("maps/testing.cub");
	/////////////////////////////

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	int_map = malloc(sizeof(char **));
	num_line = 0;
	num_textures = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' ' || line[0] == '\t'))
		{
			int_map[num_line++] = get_int_array(line);
			line = get_next_line(fd);
			int_map = ft_realloc(int_map, sizeof(char **) * (num_line + 1));
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
			line = get_next_line(fd);
		}
	}
	int_map[num_line] = NULL;
	map_builder(int_map, MAPSCALE, &cub->map, &cub->player);
	return(EXIT_SUCCESS);
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

void	print_map_resume(t_map *map)
{
	int num;

	num = 0;
	while (map->textures[num].valid)
		num++;
	printf("Num textures \t [%d]\n", num);
	num = 0;
	while (map->objets[num].valid)
		num++;
	printf("Num objets \t [%d]\n", num);
}

int	add_texture(char *path, t_texture *textures, t_mlx *screen, int type)
{
	char	*str_trimed;

	while(textures->valid)
		textures++;
	str_trimed = ft_str_trim(path + 3);
	textures->path = ft_substr(str_trimed, 0, ft_strlen(path) - 1);
	free (str_trimed);
	textures->img.ptr = mlx_xpm_file_to_image(screen->handler, "./textures/wall.xpm", &textures->width, &textures->height);
	if (textures->img.ptr == NULL)
		return (EXIT_FAILURE);
	textures->img.addr = mlx_get_data_addr(textures->img.ptr, NULL, NULL, NULL);
	if (textures->img.addr == NULL)
		return (EXIT_FAILURE);
	textures->valid = true;
	textures->type = type;
	textures->img.matrix = get_image_matrix(textures->img.addr, textures->width, textures->height);
	return (EXIT_SUCCESS);
	//Mirar si hace falta realloc
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

int	*get_int_array(char *line)
{
	int	*line_int;
	int	num_row;

	line_int = ft_calloc(sizeof(int), ft_strlen(line) + 1);

	num_row = 0;
	while(line[num_row])
	{
		if (line[num_row] == '1')
			line_int[num_row] = 1;
		if (line[num_row] == 'N')
			line_int[num_row] = 'N';
		if (line[num_row] == 'S')
			line_int[num_row] = 'S';
		if (line[num_row] == 'E')
			line_int[num_row] = 'E';
		if (line[num_row] == 'W')
			line_int[num_row] = 'W';
		num_row++;
	}
	line_int[num_row] = 255;
	return (line_int);
}

int	map_builder(int **int_map, int scale, t_map *map, t_player *player)
{
	int			num_obj;
	int			row;
	int			col;
	t_point		scaner;

	num_obj = 0;
	while (map->objets[num_obj].valid)
		num_obj++;
	scaner.x = 0;
	scaner.y = 0;
	row = 0;
	col = 0;
	while(int_map[row])
	{
		while(int_map[row][col] != 255)
		{
			if (int_map[row][col] > 1)
			{
				player->pos.x = scaner.x;
				player->pos.y = scaner.y;
				player->front = get_geo_vector((char)int_map[row][col]);
				player->cam = player->front;
			}
			if ( (int_map[row][col] == 1 && col == 0) || (int_map[row][col] == 1 && col != 0 && int_map[row][col - 1] == 0))
			{
				map->objets[num_obj].valid = 1;
				map->objets[num_obj].is_collider = 1;
				map->objets[num_obj].type = WALL;
				map->objets[num_obj].polygon.color = SUPERAZUL;
				map->objets[num_obj].polygon.line[0].texture = &map->textures[0];
				map->objets[num_obj].polygon.line[1].texture = &map->textures[0];
				map->objets[num_obj].polygon.line[2].texture = &map->textures[0];
				map->objets[num_obj].polygon.line[3].texture = &map->textures[0];
				map->objets[num_obj].polygon.line[0].p1.x = scaner.x;
				map->objets[num_obj].polygon.line[0].p1.y = scaner.y;
				map->objets[num_obj].polygon.line[3].p1.x = scaner.x;
				map->objets[num_obj].polygon.line[3].p1.y = scaner.y + scale;
				map->objets[num_obj].polygon.line[3].p2 = map->objets[num_obj].polygon.line[0].p1;
			}
			if ((int_map[row][col] == 0 && col > 0 && int_map[row][col - 1] == 1) || (int_map[row][col + 1] == 1 && int_map[row][col + 1] == 255))
			{
				map->objets[num_obj].polygon.line[0].p2.x = scaner.x;
				map->objets[num_obj].polygon.line[0].p2.y = scaner.y;
				map->objets[num_obj].polygon.line[1].p1 = map->objets[num_obj].polygon.line[0].p2;
				map->objets[num_obj].polygon.line[1].p2.x = scaner.x;
				map->objets[num_obj].polygon.line[1].p2.y = scaner.y + scale;
				map->objets[num_obj].polygon.line[2].p1 = map->objets[num_obj].polygon.line[1].p2;
				map->objets[num_obj].polygon.line[2].p2.x = map->objets[num_obj].polygon.line[0].p1.x;
				map->objets[num_obj].polygon.line[2].p2.y = scaner.y + scale;
				num_obj++;
			}
			scaner.x += scale;
			col++;
		}
		col = 0;
		row++;
		scaner.x = 0;
		scaner.y += scale;
	}
	return(EXIT_SUCCESS);
}


void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (ft_calloc(size, 1));
	if (!size)
		return (ptr);
	new_ptr = ft_calloc(size, 1);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}
