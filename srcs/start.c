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
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		if (fdf->map->elevation <= 5)
			fdf->map->elevation += 0.05;
			
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		if (fdf->map->elevation >= 0.05)
			fdf->map->elevation -= 0.05;
			
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->offset_y -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->offset_y += 5;
		
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->offset_x -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->offset_x += 5;
		
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		fdf->map->zoom += 0.015;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		fdf->map->zoom -= 0.015;
		
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
		fdf->map->alpha += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
		fdf->map->alpha -= 0.02;
		
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
		fdf->map->beta += 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_4))
		fdf->map->beta -= 0.02;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_R))
	{
		fdf->map->alpha = 1.57;
		//fdf->map->beta = 2;
	}
	
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_M))
		fdf->map->map_colour = -(fdf->map->map_colour);
	
	display_menu(fdf);
	reset_image(fdf);

	draw_image(fdf);

}

void	reset_image(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while ((uint32_t)++i < fdf->img->width)
	{
		j = -1;
		while ((uint32_t)++j < fdf->img->height)
		{
			mlx_put_pixel(fdf->img, i, j, 0x000000FF);
		}
	}
}

void	drawing_algo(t_fdf *fdf, t_fpoint start, t_fpoint end)
{
	t_delta	delta;
	int		i;

	delta.dx = end.x - start.x;
	delta.dy = end.y - start.y;
	if (fabs(delta.dx) >= fabs(delta.dy))
		delta.step = fabs(delta.dx);
	else
		delta.step = fabs(delta.dy);
	delta.dx = delta.dx / delta.step;
	delta.dy = delta.dy / delta.step;
	delta.x = start.x;
	delta.y = start.y;
	i = 0;
	while (i++ <= delta.step)
	{
		if ((uint32_t)delta.x + fdf->map->offset_x < fdf->img->width
			&& (uint32_t)delta.y + fdf->map->offset_y < fdf->img->height)
		{
			mlx_put_pixel(fdf->img, delta.x + fdf->map->offset_x,
			delta.y + fdf->map->offset_y, start.colour);
		}
		delta.x += delta.dx;
		delta.y += delta.dy;
	}
}

void	draw_line(t_fdf *fdf, int x, int y)
{
	if (x == fdf->map->rows && y == fdf->map->cols)
		return ;
	if (x + 1 < fdf->map->rows)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x + 1][y]);
	}
	if (y + 1 < fdf->map->cols)
	{
		drawing_algo(fdf, fdf->map->fgrid[x][y], fdf->map->fgrid[x][y + 1]);
	}
}

void	draw_image(t_fdf *fdf)
{
	int			i;
	int			j;

	set_projection(fdf->map);
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

void	display_menu(t_fdf *fdf)
{
	int	x;
	int	y;
	char	*str;

	str = ft_itoa(fdf->map->elevation);
	x = 20;
	y = 20;
	mlx_put_string(fdf->mlx, "WELCOME TO MY FDF", x, y);
	mlx_put_string(fdf->mlx, str, x, y + 20);
	free(str);
}

int	init_window(t_map *env)
{
	t_fdf		fdf;

	fdf.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	fdf.img = mlx_new_image(fdf.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf.mlx || !fdf.img)
		return (EXIT_FAILURE);
	fdf.map = env;
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_delete_image(fdf.mlx, fdf.img);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
