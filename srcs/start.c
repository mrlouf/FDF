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

mlx_image_t	*draw_image(mlx_t *mlx, t_point **matrix)
{
	mlx_image_t	*img;
	t_point		*tmp;

	tmp = *matrix;
	img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	
		//mlx_put_pixel(img, i + (tmp->y * 15), j + (tmp->x * 15), 0xFF0000);
	
	int i = WINDOW_WIDTH/3, j = WINDOW_HEIGHT/3;
	int interval = 40;
	while (tmp != NULL)
	{
		while (j + ((tmp->x)++ * interval) <= (j + ((tmp->x)++ * interval)))
		mlx_put_pixel(img, i + (tmp->y * interval), (j + (tmp->x * interval)), 0xFF);
		tmp = tmp->next;
	}

	/*while (tmp != NULL)
	{
		while (j <= (tmp->x * 15))
			mlx_put_pixel(img, 0 + (tmp->y * 15), j++, 0xFF0000);
		tmp = tmp->next;
	}*/
	return (img);
}

int	init_window(t_point **matrix)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "FDF@nponchon", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img = draw_image(mlx, matrix);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
