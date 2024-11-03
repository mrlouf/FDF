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

int	count_points(char **map)
{
	int	nb;
	int	i;
	int	buf;

	nb = 0;
	i = 0;
	while (map[0][i])
	{
		if (ft_isalnum(map[0][i])
		&& (map[0][i + 1] == ' ' || map[0][i + 1] == '\n'))
			nb++;
		i++;
	}
	i = 1;
	buf = nb;
	while (map[i++])
		nb += buf;
	ft_printf("nb of points = %d\n", nb);
	return (nb);
}

void	get_alt_and_colour(t_point *point, char *str)
{
	point->z = ft_atoi(str);
	point->colour = ft_atoi_base((ft_strchr(str, ',') + 3), 16);
	printf("alt = %d, colour = %d\n", point->z, point->colour);
}

t_point	**set_matrix(t_point **matrix, char **map)
{
	int	i;
	int	j;
	char	**line_tab;
	t_point *new;

	i = -1;
	while (map[++i])
	{
		line_tab = ft_split(map[i], ' ');
		ft_printf("map = %s\n", line_tab[i]);
		j = -1;
		while (line_tab[++j])
		{
			new = new_point(i, j, 0, 0);
			if (!new)
				print_error(ENOMEM);
			if (ft_strchr(line_tab[j], ',') != NULL)
				get_alt_and_colour(new, line_tab[j]);
			else
				new->z = ft_atoi(line_tab[j]);
			point_addback(matrix, new);
		}
		free_array(line_tab);
	}
	return (matrix);
}

t_point	**get_matrix(char **map)
{
	t_point	**matrix;
	int		nb_pts;

	nb_pts = count_points(map);
	matrix = (t_point **)malloc(sizeof(t_point *) * (nb_pts + 1));
	if (!matrix)
	{
		free_array(map);
		print_error(ENOMEM);
	}
	matrix[0] = NULL;
	matrix[nb_pts] = NULL;
	matrix = set_matrix(matrix, map);
	print_matrix(matrix);
	//init_window();
	return (matrix);
}
