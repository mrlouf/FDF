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
/*
void	bresenham(mlx_image_t *img, t_point start, t_point end)
{
	int		error[2];
	t_point	tmp;
	
	tmp.x = start.x;
	tmp.y = start.y;
	tmp.colour = start.colour;
	error[0] = abs(end.x - start.x) - abs(end.y - start.y);
	while (tmp.x < end.x || tmp.y < end.y)
	{
		if ((uint32_t)tmp.x < img->width && (uint32_t)tmp.y < img->height)
			mlx_put_pixel(img, tmp.x, tmp.y, 0xFFFFFF);
		if (error[1] > -abs(end.y - start.y))
		{
			error[0] -= abs(end.y - start.y);
			tmp.x += (start.x < end.x);
			tmp.x -= (end.x < start.x);
		}
		if (error[1] < abs(end.x - start.x))
		{
			error[0] += abs(end.x - start.x);
			tmp.y += (start.y < end.y);
			tmp.y -= (end.y < start.y);
		}
	}
}
*/

void	bresenham(mlx_image_t *img, t_point start, t_point end)
{
	t_point	tmp;

	tmp.x = start.x;
	tmp.y = start.y;
	if (start.z != 0)
		tmp.colour = 0xfee08bff;
	else
		tmp.colour = start.colour;
	if ((uint32_t)tmp.x < img->width && (uint32_t)tmp.y < img->height)
	{
		while (tmp.x <= end.x)
			mlx_put_pixel(img, (tmp.x)++, tmp.y, tmp.colour);
		tmp.x = start.x;
		while (tmp.y <= end.y)
			mlx_put_pixel(img, tmp.x, (tmp.y)++, tmp.colour);
	}
}

void	draw_line(mlx_image_t *img, t_map *env, int x, int y)
{
	if (x == env->rows && y == env->cols)
		return ;
	if (x + 1 < env->rows)
	{
		bresenham(img, env->grid3d[x][y], env->grid3d[x + 1][y]);
	}
	if (y + 1 < env->cols)
	{
		bresenham(img, env->grid3d[x][y], env->grid3d[x][y + 1]);
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
