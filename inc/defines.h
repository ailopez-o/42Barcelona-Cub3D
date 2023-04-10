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
# include <stddef.h>
# include <stdlib.h>
# include "keycodes.h"

# define WINX 1200
# define WINY 800



typedef struct s_cub	t_cub;
typedef struct s_mlx	t_mlx;
typedef struct s_point	t_point;
typedef struct s_line	t_line;
typedef struct s_player	t_player;

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

struct s_player
{
	t_point	position;
	float	orientation;
};

struct s_cub
{
	t_mlx	screen;
	char	**map;
	t_line	*walls;
};

#endif