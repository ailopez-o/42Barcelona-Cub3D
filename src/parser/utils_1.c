/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:52 by framos-p          #+#    #+#             */
/*   Updated: 2023/12/15 15:12:47 by framos-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"
#include "mlx.h"

char	*ft_str_trim(char *str)
{
	int		start;
	int		end;
	char	*new_str;

	end = ft_strlen(str) - 1;
	start = 0;
	while (str[start] == ' ')
		start++;
	while (str[end] == ' ' || str[end] == '\n')
		end--;
	if (end < start)
		return (ft_strdup(""));
	new_str = ft_substr(str, start, end - start + 1);
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	void	*calloc_result;

	if (ptr == NULL)
	{
		calloc_result = ft_calloc(size, 1);
		if (!calloc_result)
			return (NULL);
		else
			return (calloc_result);
	}
	if (!size)
		return (ptr);
	new_ptr = ft_calloc(size, 1);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

int	free_double(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (EXIT_SUCCESS);
}
