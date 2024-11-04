/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

t_point	*new_point(int x, int y, int z, int colour)
{
	t_point	*new;

	new = malloc(sizeof(t_point));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->colour = colour;
	new->next = NULL;
	return (new);
}

t_point	*matrix_last(t_point *matrix)
{
	t_point	*last;

	if (matrix == NULL)
		return (NULL);
	last = matrix;
	while (last->next)
		last = last->next;
	return (last);
}

void	point_addback(t_point **matrix, t_point *new)
{
	t_point	*tmp;

	if (!new)
		return ;
	if (*matrix == NULL)
		*matrix = new;
	else
	{
		tmp = matrix_last(*matrix);
		tmp->next = new;
	}
}

void	print_matrix(t_point **matrix)
{
	t_point	*tmp;

	tmp = *matrix;
	while (tmp->next != NULL)
	{
		ft_printf("x = %d, y = %d, z = %d, colour = %d\n", \
		tmp->x, tmp->y, tmp->z, tmp->colour);
		tmp = tmp->next;
	}
	ft_printf("x = %d, y = %d, z = %d, colour = %d\n", \
	tmp->x, tmp->y, tmp->z, tmp->colour);
}
