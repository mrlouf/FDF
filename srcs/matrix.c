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

/*	Get the total number of points, including ones with colours	*/

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

void	get_alt_and_colour(char *str, t_point *point)
{
	point->z = ft_atoi(str);
	point->colour = ft_atoi_base((ft_strchr(str, ',') + 3), 16);
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
		if (ft_strchr(line_tab[j], ',') != NULL)
			get_alt_and_colour(line_tab[j], point);
		else
			point->z = ft_atoi(line_tab[j]);
		env->max = get_max(env->max, point->z);
		env->min = get_min(env->min, point->z);
	}
	free_array((void **)line_tab);

}

static void	malloc_grid(t_map *env)
{
	int	i;

	env->grid3d = malloc(sizeof(t_point *) * env->rows);
	if (!(env->grid3d))
	{
		free_array((void **)env->grid3d);
		print_error(ENOMEM);
	}
	i = -1;
	while (++i < env->rows)
	{
		env->grid3d[i] = malloc(sizeof(t_point) * env->cols);
		if (!(env->grid3d[i]))
		{
			free_array((void **)env->grid3d);
			print_error(ENOMEM);
		}
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
	//print_matrix(env);
	init_window(env);
}
