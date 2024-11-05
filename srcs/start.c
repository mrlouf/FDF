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

mlx_image_t	*draw_image(mlx_t *mlx, t_map *env)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
	
	int offset_x = WINDOW_WIDTH/3, offset_y = WINDOW_HEIGHT/3; // TODO put this offset directly in the base number value
	int i = -1;
	while (++i < env->rows)
	{
		int j = -1;
		while (++j < env->cols)
			mlx_put_pixel(img, j + env->grid3d[i][j].x + offset_x, i + env->grid3d[i][j].y + offset_y, 0xFFFFFF);
	}

	return (img);
}

int	init_window(t_map *env)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img = draw_image(mlx, env);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
