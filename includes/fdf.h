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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

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
	int	x;
	int	y;
	int	z;
	int	colour;
}	t_point;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		max;
	int		min;
	int		interval;
	char	**grid2d;
	t_point	**grid3d;
}	t_map;

//		CHECK AND PARSE INPUT

void	check_input(char *file, t_map *env);
void	get_content(int fd, t_map *env);
int		check_extension(char *file);
int		count_rows(int fd);
int		count_rows(int fd);

//		SET MATRIX

void	init_env(t_map *env);
void	get_matrix(t_map *env);
void	set_matrix(t_map *env);
void	count_columns(t_map *env);
void	get_columns(t_map *env, int i);
int		get_max(int	a, int b);
int		get_min(int	a, int b);

//		WINDOW AND DRAWING

int		init_window(t_map *env);
void	ft_hook(void* param);

//		ERROR, FREE & DEBUG

void	print_error(int err);
void	free_array(void **array);
void	free_matrix(t_point **matrix);
void	print_matrix(t_map *env);

#endif
