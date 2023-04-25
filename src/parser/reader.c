
#include "defines.h"
#include "utils.h"
#include "mlx.h"
#include "geometry.h"
#include <fcntl.h>

void	*ft_realloc(void *ptr, size_t size);
int		*get_int_array(char *line);
int		map_builder(int **int_map, int scale, t_map *map, t_player *player);
char	**get_image_matrix(char *data, int width, int height);

int	load_map(char *path, t_cub *cub)
{
	int		fd;
	char	*line;
	int		**int_map;
	int		num_line;
	int		num_textures;

	cub->map.objets = ft_calloc(1, sizeof(t_objet) * 300);
	cub->map.textures = ft_calloc(1, sizeof(t_texture) * 100);

	/////////////////// HARDCODER
	path = ft_strdup("maps/testing.cub");
	/////////////////////////////

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);

	/////////////////// HARDCODER
	cub->map.textures[0].path = ft_strdup("textures/bluestone.xpm");
	cub->map.textures[0].img.ptr = mlx_xpm_file_to_image(cub->screen.handler, cub->map.textures[0].path, &cub->map.textures[0].width, &cub->map.textures[0].height);
	cub->map.textures[0].valid = true;
	cub->map.textures[0].type = WALL;
	cub->map.textures[0].img.matrix = get_image_matrix(cub->map.textures[0].img.ptr, cub->map.textures[0].width, cub->map.textures[0].height);
	/////////////////////////////

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
			
			//DATA
			//printf("data >> %s", line);
			free(line);
			line = get_next_line(fd);
		}
	}
	int_map[num_line] = NULL;
	//get_polygons(int_map, MAPSCALE, map->objets, &map->textures[0]);
	map_builder(int_map, MAPSCALE, &cub->map, &cub->player);
	return(EXIT_SUCCESS);
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

//int	get_polygons(int **int_map, int scale, t_objet *objets, t_texture *texture)
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
