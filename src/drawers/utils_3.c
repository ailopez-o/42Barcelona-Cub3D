/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:29:04 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/23 14:33:30 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include <math.h>
#include "geometry.h"

int		*get_texture_column(t_line *wall, t_point point);
int		*get_texture_column_fix(t_colision *colision);
int		calculate_new_height(double distance, int texture_height);
int		*create_new_column(int new_height);
void	populate_new_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height);
void	populate_larger_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height);
int		*adjust_column_if_greater_than_winy(int *new_column, double distance,
			int *new_height);
void	rotate_texture(int *column, int height);

int	*adjust_column(t_colision *colision, double distance)
{
	int	*new_column;
	int	*texture_stripe;
	int	new_height;

	texture_stripe = get_texture_column(&colision->line, colision->point);
	if (distance < colision->line.texture->height)
		new_height = calculate_new_height(distance,
				colision->line.texture->height);
	else
		new_height = (int)distance;
	new_column = create_new_column(new_height);
	if (!new_column)
		return (NULL);
	if (distance < colision->line.texture->height)
		populate_new_column(new_column, texture_stripe, new_height,
			colision->line.texture->height);
	else
		populate_larger_column(new_column, texture_stripe, new_height,
			colision->line.texture->height);
	if (distance > WINY)
		new_column = adjust_column_if_greater_than_winy(new_column,
				distance, &new_height);
	if (new_column)
		rotate_texture(new_column, new_height);
	return (new_column);
}

int	calculate_new_height(double distance, int texture_height)
{
	return ((int)(texture_height * distance / (double)texture_height));
}

int	*create_new_column(int new_height)
{
	int	*new_column;

	new_column = malloc(new_height * sizeof(int));
	return (new_column);
}

void	populate_new_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height)
{
	int	i;

	i = -1;
	while (++i < new_height)
		new_column[i] = texture_stripe[i * texture_height / new_height];
}

void	populate_larger_column(int *new_column, int *texture_stripe,
			int new_height, int texture_height)
{
	int	i;

	i = -1;
	while (++i < new_height)
		new_column[i] = texture_stripe[i * texture_height / new_height
			% texture_height];
}
