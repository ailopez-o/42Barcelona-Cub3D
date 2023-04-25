#include "defines.h"
#include "utils.h"
#include <fcntl.h>

void	*ft_realloc(void *ptr, size_t size);
int		*get_int_array(char *line);
int		get_polygons(int **int_map, int scale, t_objet *objets);

int	load_map(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		**int_map;
	int		num_line;

	path = ft_strdup("/Users/aitoraudicana/42Barcelona/cursus/cube3D/maps/testing.cub");

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);

	map->objets = ft_calloc(1, sizeof(t_objet) * 100);
	int_map = malloc(sizeof(char **));
	num_line = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] && (line[0] == '0' || line[0] == '1' || line[0] == ' ' || line[0] == '\t'))
		{
			printf("%s", line);
			int_map[num_line++] = get_int_array(line);
			line = get_next_line(fd);
			int_map = ft_realloc(int_map, sizeof(char **) * (num_line + 1));
		}
		else
		{
			//DATA
			printf("data >> %s", line);
			free(line);
			line = get_next_line(fd);
		}
	}
	int_map[num_line] = NULL;
	get_polygons(int_map, MAPSCALE, map->objets);
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
		num_row++;
	}
	line_int[num_row] = 255;
	return (line_int);
}


int	get_polygons(int **int_map, int scale, t_objet *objets)
{
	int			num_obj;
	int			row;
	int			col;
	t_point		scaner;

	num_obj = 0;
	while (objets[num_obj].valid)
		num_obj++;
	scaner.x = 0;
	scaner.y = 0;
	row = 0;
	col = 0;
	while(int_map[row])
	{
		while(int_map[row][col] != 255)
		{
			if ((int_map[row][col] == 1 && int_map[row][col - 1] == 0) || (int_map[row][col] == 1 && col == 0))
			{
				objets[num_obj].valid = 1;
				objets[num_obj].is_collider = 1;
				objets[num_obj].type = WALL;
				objets[num_obj].polygon.p1.x = scaner.x;
				objets[num_obj].polygon.p1.y = scaner.y;
				objets[num_obj].polygon.p4.x = scaner.x;
				objets[num_obj].polygon.p4.y = scaner.y + scale;
				objets[num_obj].polygon.color = SUPERAZUL;
			}
			if ((int_map[row][col] == 0 && int_map[row][col - 1] == 1) || (int_map[row][col + 1] == 1 && int_map[row][col + 1] == 255))
			{
				objets[num_obj].polygon.p2.x = scaner.x;
				objets[num_obj].polygon.p2.y = scaner.y;
				objets[num_obj].polygon.p3.x = scaner.x;
				objets[num_obj].polygon.p3.y = scaner.y + scale;
				num_obj++;
				//objets = ft_realloc(objets, sizeof(t_objet) * num_obj);
				objets[num_obj].valid = false;
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
