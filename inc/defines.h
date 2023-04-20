/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:50:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/19 22:25:03 by bmoll-pe         ###   ########.fr       */
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

# define WIN2D 		1000
# define WINY 		800
# define WINX WIN2D * 2
# define FOV		60

# define X 0
# define Y 1

# define ROJO 		0xc1272d
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
# define BGCOLOR	0x000000

# define	NULL_OBJET	0
# define	WALL		1
# define	DOOR		2
# define	SPRITE		3


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
	int 	color;
};

struct s_line
{
	t_point	p1;
	t_point	p2;
};

struct s_vector
{
	t_point	*pos;
	float	dir[2];
};

struct s_colision
{
	t_point	point;
	t_line	line;
	float	angle;
	float	distance;
	bool	valid;
};

struct s_polygon
{
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;
	void	*texture;
	int		color;
};

struct s_objet
{
	t_polygon	polygon;
	int			type;
	bool		is_collider;
};

struct s_player
{
	t_point		pos;
	t_vector	front;
	t_vector	cam;
	t_colision	*ray_colider;
};

struct s_cub
{
	t_mlx		screen;
	t_player	player;
	char		**map;
	t_objet		*objets;
};

#endif