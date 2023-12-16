/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:14:53 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/04 17:01:49 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <math.h>
# include "keycodes.h"
# include "libft.h"

# define FOV				70
# define WINY 				800
# define WIN2D 				1200
# define WINX				1200
# define MAPSCALE			64
# define MINIMAPSCALE		4
# define MINIMAPCOLOR		DARK_RED

# define PLYSPEED			10
# define PLYROTSPEED		4
# define PLYVIEW			15000
# define PLYCOLLIDE			10
# define STOP				0
# define GO_FRONT			1
# define GO_BACK			2
# define GO_RIGHT			4
# define GO_LEFT			8
# define ROTATE_L			1
# define ROTATE_R			2

# define NO	1
# define SO	2
# define WE	3
# define EA	4
# define F	5
# define C	6
# define SC	7

# define X 0
# define Y 1

# define ROJO 		0xc1272d
# define DARK_RED	0x7d1e21
# define VERDE		0x33cc55
# define FUCSIA 	0xff255c
# define AZUL		0x1B8EFA
# define SUPERAZUL	0x0000FF
# define CARBON		0x151515
# define WHITE		0xBBBBBB
# define DISCO		0x9A1F6A
# define BRICK_RED	0xC2294E
# define FLAMINGO	0xEC4B27
# define JAFFA		0xEF8633
# define SAFFRON	0xF3AF3D
# define BLACK		0x151515
# define BGCOLOR	0x151515
# define SKYCOLOR	0x171717
# define AMARILLO	0xFFFEA1

# define WALLCOLOR			ROJO
# define DARKWALL			DARK_RED
# define PLAYER_COLOR		VERDE
# define RAY_COLOR_START 	WHITE
# define RAY_COLOR_END		AMARILLO

typedef enum block_type
{
	NULL_OBJET,
	WALL,
	DOOR,
	SPRITE,
}	t_block_type;

typedef struct s_cub		t_cub;
typedef struct s_mlx		t_mlx;
typedef struct s_point		t_point;
typedef struct s_line		t_line;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_vector		t_vector;
typedef struct s_colision	t_colision;
typedef struct s_objet		t_objet;
typedef struct s_polygon	t_polygon;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_texture	t_texture;
typedef struct s_params		t_params;
typedef struct s_ray		t_ray;
typedef struct s_ptr		t_ptr;
typedef struct s_mapdata	t_mapdata;
typedef struct s_pars		t_pars;
typedef struct s_data		t_data;


struct s_data
{
	int		x;
	int		y;
	char	**map;
	bool	closed;
	char	**visited;
	int		width;
	int		height;
};


struct s_ptr
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	*img_data;
};

struct s_mlx
{
	void	*handler;
	void	*win;
	void	*img;
	char	*img_buff;
	int		bitxpixel;
	int		lines;
	int		endian;
};

struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
};

struct s_mapdata
{
	t_point	scaner;
	int		num_obj;
	int		row;
	int		col;
	char	c;
};

struct s_line
{
	t_point		p1;
	t_point		p2;
	t_texture	*texture;
};

struct s_vector
{
	float	dir[2];
};

struct s_colision
{
	t_point	point;
	t_line	line;
	float	distance;
	bool	valid;
};

struct s_params
{
	t_mlx	*screen;
	t_point	start;
	t_point	end;
	int		*column;
	bool	b_shadow;
};

struct s_ray
{
	float		ang;
	int			num_colision;
	float		line_height;
	float		orto_dist;
	float		dot_product;
	float		magnitude_v1;
	float		magnitude_v2;
	float		angle;

};

struct s_polygon
{
	t_line		line[4];
	int			color;
};

struct s_objet
{
	t_polygon	polygon;
	int			type;
	bool		is_collider;
	bool		valid;
};

struct s_player
{
	t_point		pos;
	t_point		matrix_pos;
	t_vector	front;
	t_vector	cam;
	t_colision	ray_colider[WIN2D + 1];
	int			move;
	int			rotate;
	float		player_speed;
	float		player_rot_speed;
	char		init_view;
};

struct s_img
{
	void			*ptr;
	char			*addr;
	int				**matrix;
	int				bpp;
	int				linesize;
	int				endian;
	int				width;
	int				height;
};

struct s_texture
{
	int		valid;
	int		type;
	char	*path;
	t_img	img;
	int		width;
	int		height;
};

struct s_pars
{
	int		num_line;
	int		num_textures;
	int		data_type;
	bool	map_parsing;
};


struct s_map
{
	t_objet		objets[1000];
	t_texture	textures[10];
	int			scale;
	int			bottom_color;
	int			top_color;
	int			max_x;
	int			max_y;
};

struct s_cub
{
	t_mlx		screen;
	t_player	player;
	t_map		map;
	float		fov_dist;
	int			fov;
};

#endif
