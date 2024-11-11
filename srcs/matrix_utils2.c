/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:04:54 by nponchon          #+#    #+#             */
/*   Updated: 2024/11/11 13:04:56 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	apply_rotations(t_map *env, int i, int j)
{
	env->fgrid[i][j].x = env->grid3d[i][j].x;
	env->fgrid[i][j].y = env->grid3d[i][j].y;
	env->fgrid[i][j].z = env->grid3d[i][j].z;
	env->fgrid[i][j].y = env->fgrid[i][j].y * cos(env->zrotate)
		+ env->fgrid[i][j].z * sin(env->zrotate);
	env->fgrid[i][j].z = -env->fgrid[i][j].y * sin(env->zrotate)
		+ env->fgrid[i][j].z * cos(env->zrotate);
	env->fgrid[i][j].x = env->fgrid[i][j].x * cos(env->xrotate)
		+ env->fgrid[i][j].z * sin(env->xrotate);
	env->fgrid[i][j].z = -env->fgrid[i][j].x * sin(env->xrotate)
		+ env->fgrid[i][j].z * cos(env->xrotate);
	env->fgrid[i][j].x = env->fgrid[i][j].x * cos(env->yrotate)
		- env->fgrid[i][j].y * sin(env->yrotate);
	env->fgrid[i][j].y = env->fgrid[i][j].x * sin(env->yrotate)
		+ env->fgrid[i][j].y * cos(env->yrotate);
}
