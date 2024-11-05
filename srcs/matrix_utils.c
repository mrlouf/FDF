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

void	print_matrix(t_map *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->rows)
	{
		j = -1;
		while (++j < env->cols)
			ft_printf("%d,%d,%d ", env->grid3d[i][j].x,
				env->grid3d[i][j].y, env->grid3d[i][j].z);
		ft_printf("\n");
	}
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
