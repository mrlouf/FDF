/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:54:24 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 18:54:26 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	free_array(void **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

/*void	free_matrix(t_point **matrix)
{
	t_point	*tmp;

	if (matrix == NULL)
		return ;
	while ((*matrix)->next)
	{
		tmp = (*matrix)->next;
		free(*matrix);
		(*matrix) = tmp;
	}
	free(*matrix);
	free(matrix);
	matrix = NULL;
}*/

void	print_error(int err)
{
	errno = err;
	perror("Error");
	exit(EXIT_FAILURE);
}
