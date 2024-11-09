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
	t_fdf	*fdf;

	fdf = param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->elevation += 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->elevation -= 0.05;
	draw_image(fdf);
}

void	drawing_algo(mlx_image_t *img, t_fpoint start, t_fpoint end)
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	step;
	int		i;

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
		if ((uint32_t)x + (WINDOW_WIDTH / 2) < img->width && (uint32_t)y + (WINDOW_HEIGHT / 8) < img->height)
		{
			mlx_put_pixel(img, x + (WINDOW_WIDTH / 2), y + (WINDOW_HEIGHT / 8), start.colour);
		}
		x += delta_x;
		y += delta_y;
	}
}

void	draw_line(t_fdf *fdf, int x, int y)
{
	if (x == fdf->map->rows && y == fdf->map->cols)
		return ;
	if (x + 1 < fdf->map->rows)
	{
		drawing_algo(fdf->img, fdf->map->fgrid[x][y], fdf->map->fgrid[x + 1][y]);
	}
	if (y + 1 < fdf->map->cols)
	{
		drawing_algo(fdf->img, fdf->map->fgrid[x][y], fdf->map->fgrid[x][y + 1]);
	}
}

void	draw_image(t_fdf *fdf)
{
	int			i;
	int			j;

	//fdf->img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	project(fdf->map);
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			draw_line(fdf, i, j);
		}
	}
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
	t_fdf		fdf;

	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_memset(fdf.img->pixels, 0, fdf.img->width * fdf.img->height * sizeof(int32_t));
	if (!fdf.mlx)
		return (EXIT_FAILURE);
	fdf.map = env;
	display_menu(fdf.mlx);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
