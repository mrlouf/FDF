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

/*	alpha = 0.78 radians or 45 degrees	*/

void	init_env(t_map *env)
{
	env->rows = 0;
	env->cols = 0;
	env->max = 0;
	env->min = 0;
	env->interval = 100;
	env->altitude = 1;
	env->alpha = 0.78;
	env->zoom = 12.5;
}

int	main(int ac, char **av)
{
	t_map	env;

	if (ac == 2)
	{
		init_env(&env);
		check_input(av[1], &env);
		set_matrix(&env);
		free_array((void **)env.grid2d);
		free_matrix(&env);
		init_window(&env);
	}
	else
		print_error(EINVAL);
	return (EXIT_SUCCESS);
}
