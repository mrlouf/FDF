/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:07:10 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 11:03:57 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_error(int err)
{
	errno = err;
	perror("Error");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
	/*		TODO
		- Receive the input (single *.fdf file), otherwise print error
		- Parse the input with GNL and check for error (wrong format, wrong content etc.)
		- 
	*/
		//check_format(av[1]);

	}
	else
		print_error(EINVAL);
	return (0);
}
