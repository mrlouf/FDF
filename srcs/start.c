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

void	drawing_algo(mlx_image_t *img, t_fpoint start, t_fpoint end)
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	step;
	int		i;

	//printf("start.x=%d start.y=%d\n", start.x, start.y);
	//printf("end.x=%d end.y=%d\n", end.x, end.y);
	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	if (fabs(delta_x) >= fabs(delta_y))
		step = fabs(delta_x);
	else
		step = fabs(delta_y);
	delta_x = delta_x / step;
	delta_y = delta_y / step;
	x = start.x;
	y = start.y;
	i = 0;
	while(i++ <= step)
	{
		if ((uint32_t)x + (WINDOW_WIDTH / 2) < img->width && (uint32_t)y + (WINDOW_HEIGHT / 4) < img->height)
		{
			mlx_put_pixel(img, x + (WINDOW_WIDTH / 2), y + (WINDOW_HEIGHT / 4), start.colour);
		}
		x += delta_x;
		y += delta_y;
	}
}

void	draw_line(mlx_image_t *img, t_map *env, int x, int y)
{
	if (x == env->rows && y == env->cols)
		return ;
	if (x + 1 < env->rows)
	{
		drawing_algo(img, env->fgrid[x][y], env->fgrid[x + 1][y]);
	}
	if (y + 1 < env->cols)
	{
		drawing_algo(img, env->fgrid[x][y], env->fgrid[x][y + 1]);
	}
}

mlx_image_t	*draw_image(mlx_t *mlx, t_map *env)
{
	int			i;
	int			j;
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_memset(img->pixels, 000000, img->width * img->height * sizeof(int32_t));
	i = -1;
	while (++i < env->rows)
	{
		j = -1;
		while (++j < env->cols)
			draw_line(img, env, i, j);
	}
	return (img);
}

void	display_menu(mlx_t *mlx)
{
	int	x;
	int	y;
	
	x = 20;
	y = 20;
	mlx_put_string(mlx, "WELCOME TO MY FDF", x, y);
}

int	init_window(t_map *env)
{
	mlx_t		*mlx;
	t_fdf		fdf;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	if (!mlx)
		return (EXIT_FAILURE);
	fdf.img = draw_image(mlx, env);
	display_menu(mlx);
	mlx_image_to_window(mlx, fdf.img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
