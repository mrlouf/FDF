/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 15:30:08 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

void	count_columns(t_map *env)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (env->grid2d[0][i])
	{
		if (ft_isalnum(env->grid2d[0][i])
		&& (env->grid2d[0][i + 1] == ' ' || env->grid2d[0][i + 1] == '\n'
		|| env->grid2d[0][i + 1] == '\0'))
			nb++;
		i++;
	}
	i = 1;
	env->cols = nb;
}

void	get_columns(t_map *env, int i)
{
	t_point	*point;
	char	**line_tab;
	int		j;

	line_tab = ft_split(env->grid2d[i], ' ');
	j = -1;
	while (++j < env->cols)
	{
		point = &(env->grid3d[i][j]);
		point->x = j * (env->interval);
		point->y = i * (env->interval);
		point->colour = COLOUR_FIVE;
		point->z = ft_atoi(line_tab[j]) * (env->interval);
		if (ft_strchr(line_tab[j], ',') != NULL)
			point->colour = ft_atoi_base((ft_strchr(line_tab[j], ',') + 3), 16);
		env->max = get_max(env->max, point->z);
		env->min = get_min(env->min, point->z);
	}
	free_array((void **)line_tab);
}

void	malloc_grid(t_map *env)
{
	int	i;

	env->grid3d = malloc(sizeof(t_point *) * env->rows);
	env->fgrid = malloc(sizeof(t_fpoint *) * env->rows);
	if (!(env->grid3d) || !(env->fgrid))
	{
		free_matrix(env);
		print_error(ENOMEM);
	}
	i = -1;
	while (++i < env->rows)
	{
		env->grid3d[i] = malloc(sizeof(t_point) * env->cols);
		env->fgrid[i] = malloc(sizeof(t_fpoint) * env->cols);
		if (!(env->grid3d) || !(env->fgrid))
		{
			free_matrix(env);
			print_error(ENOMEM);
		}
	}
}

void	project(t_map *env, int i)
{
	int	j;

	j = -1;
	while (++j < env->cols)
	{
		env->fgrid[i][j].x = (int)env->grid3d[i][j].x * sinf(env->alpha) \
			+ ((int)env->grid3d[i][j].z * sinf(env->alpha - 2) * 0.1);
		env->fgrid[i][j].y = (int)env->grid3d[i][j].y * cosf(env->alpha) \
			+ ((int)-env->grid3d[i][j].z * cosf(env->alpha - 2) * 0.1);
		env->fgrid[i][j].x = (env->fgrid[i][j].x / 2) - (env->fgrid[i][j].y / 2);
		env->fgrid[i][j].y = (env->fgrid[i][j].x * 0.5) + (env->fgrid[i][j].y * 0.5);
		if (env->grid3d[i][j].z > 0)
			env->fgrid[i][j].colour = COLOUR_FOUR;
		else if (env->grid3d[i][j].z < 0)
			env->fgrid[i][j].colour = COLOUR_EIGHT;
		else
			env->fgrid[i][j].colour = env->grid3d[i][j].colour;
	}
}

void	set_matrix(t_map *env)
{
	int		i;

	count_columns(env);
	malloc_grid(env);
	i = -1;
	while (env->grid2d[++i] != NULL)
		get_columns(env, i);
	i = -1;
	while (env->grid2d[++i] != NULL)
		project(env, i);
}
