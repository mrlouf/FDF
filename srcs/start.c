/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:15:12 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 10:15:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}


void	bresenham(mlx_image_t *img, t_fpoint start, t_fpoint end)
{
	int			error[2];
	t_fpoint	tmp;
	
	tmp.x = start.x;
	tmp.y = start.y;
	error[0] = fabs(end.x - start.x) - fabs(end.y - start.y);
	while (tmp.x != end.x || tmp.y != end.y)
	{
		printf("+x=%f y=%f\n", tmp.x, tmp.y);
		printf("-x=%f y=%f\n", end.x, end.y);
		if (tmp.x >= 0 && (uint32_t)tmp.x < img->width
			&& tmp.y >= 0 && (uint32_t)tmp.y < img->height)
			mlx_put_pixel(img, tmp.x, tmp.y, 0xFFFFFF);
		error[1] = 2 * error[0];
		if (error[1] > -fabs(end.y - start.y))
		{
			error[0] -= fabs(end.y - start.y);
			tmp.x += (start.x < end.x);
			tmp.x -= (end.x < start.x);
		}
		if (error[1] < fabs(end.x - start.x))
		{
			error[0] += fabs(end.x - start.x);
			tmp.y += (start.y < end.y);
			tmp.y -= (end.y < start.y);
		}
	}
}

/*
void	bresenham(mlx_image_t *img, t_fpoint start, t_fpoint end)
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	step;
	int		i;

	delta_x = fabs(end.x - start.x);
	delta_y = fabs(end.y - start.y);
	if (delta_x >= delta_y)
		step = delta_x;
	else
		step = delta_y;
	delta_x = delta_x / step;
	delta_y = delta_y / step;
	x = start.x;
	y = start.y;
	i = 0;
	while(i++ <= step)
	{
		if (x >= 0 && (uint32_t)x < img->width
			&& y >= 0 && (uint32_t)y < img->height)
		{
			printf("x=%f y=%f\n", x, y);
			mlx_put_pixel(img, x, y, 0xFFFFFF);
		}
		x += delta_x;
		y += delta_y;
	}
}*/

void	draw_line(mlx_image_t *img, t_map *env, int x, int y)
{
	printf("+x=%f y=%f\n", env->fgrid[x][y].x, env->fgrid[x][y].y);
	printf("-x=%f y=%f\n", env->fgrid[x + 1][y].x, env->fgrid[x + 1][y].y);
	if (x == env->rows && y == env->cols)
		return ;
	if (x + 1 < env->rows)
	{
		bresenham(img, env->fgrid[x][y], env->fgrid[x + 1][y]);
	}
	if (y + 1 < env->cols)
	{
		bresenham(img, env->fgrid[x][y], env->fgrid[x][y + 1]);
	}
}

mlx_image_t	*draw_image(mlx_t *mlx, t_map *env)
{
	int			i;
	int			j;
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
	i = -1;
	while (++i < env->rows)
	{
		j = -1;
		while (++j < env->cols)
			draw_line(img, env, i, j);
	}
	return (img);
}

int	init_window(t_map *env)
{
	mlx_t		*mlx;
	t_fdf		fdf;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	if (!mlx)
		return (EXIT_FAILURE);
	fdf.img = draw_image(mlx, env);
	mlx_image_to_window(mlx, fdf.img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
