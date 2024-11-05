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
# include "../MLX42/include/MLX42/MLX42.h"

# define WINDOW_WIDTH 	1920
# define WINDOW_HEIGHT 	1080

# define COLOUR_ONE 	0x1500ff
# define COLOUR_TWO 	0x005fff
# define COLOUR_THREE 	0x00d2ff
# define COLOUR_FOUR 	0x00ffb8
# define COLOUR_FIVE 	0x00ff44
# define COLOUR_SIX 	0x2fff00
# define COLOUR_SEVEN 	0xa3ff00
# define COLOUR_EIGHT 	0xffe700
# define COLOUR_NINE 	0xff7400
# define COLOUR_TEN 	0xff0000

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
	int			rows;
	int			cols;
	int			max;
	int			min;
	int			interval;
	char		**grid2d;
	t_point		**grid3d;
	mlx_image_t	*img;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*img;
}	t_fdf;

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
void	free_matrix(t_map *env);
void	print_matrix(t_map *env);

#endif
