/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

/*	TODO.
	- Open a window with MLX42
	- Draw each point
*/

int	main(int ac, char **av)
{
	char	**map;
	t_point	**matrix;

	if (ac == 2)
	{
		map = check_input(av[1]);
		matrix = get_matrix(map);
		free_array(map);
		free_matrix(matrix);
	}
	else
		print_error(EINVAL);
	return (EXIT_SUCCESS);
}
