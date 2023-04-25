/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll <bmoll@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:50:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/25 13:02:16 by bmoll            ###   ########.fr       */
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

# define WIN2D 			850
# define WINY 			800
# define WINX			1250
# define FOV			90
# define MAPSCALE		100
# define MINIMAPSCALE	0.1


# define PLYSPEED	7
# define PLYVIEW	15000
# define PLYCOLLIDE	11

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
# define WALLCOLOR	ROJO
# define DARKWALL	DARK_RED

# define	NULL_OBJET	0
# define	WALL		1
# define	DOOR		2
# define	SPRITE		3

#define		NO
#define		SO
#define		WE
#define		EA

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
	bool		valid;
};

struct s_player
{
	t_point		pos;
	t_vector	front;
	t_vector	cam;
	t_colision	*ray_colider;
};

struct s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				linesize;
	int				endian;
	int				width;
	int				height;
};

struct s_texture
{
	int		type;
	char	*path;
	t_img	img;
};

struct s_map
{	
	t_objet		*objets;
	t_texture	*textures;
	int			scale;
	int			bottom_color;
	int			top_color;
};

struct s_cub
{
	t_mlx		screen;
	t_player	player;
	t_map		map;
};

#endif