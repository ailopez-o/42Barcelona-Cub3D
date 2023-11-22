/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: framos-p <framos-p@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:47:32 by framos-p          #+#    #+#             */
/*   Updated: 2023/11/22 10:49:26 by framos-p         ###   ########.fr       */
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
	return (new_str);
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
