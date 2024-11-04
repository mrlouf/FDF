/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:11:32 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/29 16:11:35 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

//		POINT STRUCTURE (X = COL, Y = ROW, Z = ALTITUDE)

typedef struct s_point
{
	int				x;
	int				y;
	int				z;
	int				colour;
	struct s_point	*next;
}	t_point;

//		CHECK AND PARSE INPUT

char	**check_input(char *file);
char	**check_content(char *file);
char	**get_content(int fd, int count);
int		check_extension(char *file);
int		count_lines(int fd);

//		GET MATRIX

t_point	**get_matrix(char **map);
t_point	*new_point(int x, int y, int z, int colour);
void	point_addback(t_point **matrix, t_point *new);
t_point	*matrix_last(t_point *matrix);
void	print_matrix(t_point **matrix);

//		WINDOW AND DRAWING

int	init_window(void);
void ft_hook(void* param);

//		ERROR AND FREE

void	print_error(int err);
void	free_array(char **array);
void	free_matrix(t_point **matrix);

#endif
