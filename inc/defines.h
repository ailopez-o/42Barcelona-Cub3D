/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoll-pe <bmoll-pe@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:50:56 by bmoll-pe          #+#    #+#             */
/*   Updated: 2023/04/05 11:58:42 by bmoll-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdbool.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include "keycodes.h"
# include "libft.h"

# define WINX 1200
# define WINY 800

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


typedef struct s_cub	t_cub;
typedef struct s_mlx	t_mlx;
typedef struct s_point	t_point;
typedef struct s_line	t_line;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_vector	t_vector;

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
	int		stroke;
	int 	color;
};

struct s_ray
{
	t_point	pos;
	float	dir[2];
};

struct s_vector
{
	t_point	*pos;
	float	dir[2];
};

struct s_player
{
	t_point		pos;
	t_vector	front;
	t_vector	cam;
};

struct s_cub
{
	t_mlx		screen;
	char		**map;
	t_player	player;
	t_line		*walls;
};

#endif