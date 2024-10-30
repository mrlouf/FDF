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

# ifndef ROW_MAX
#  define ROW_MAX 100
# endif

# ifndef COL_MAX
#  define COL_MAX 100
# endif

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

//		CHECK AND PARSE INPUT

void	check_input(char *file);
char	**check_content(char *file);
char	**get_content(int fd);
int		check_extension(char *file);

//		ERROR AND FREE

void	print_error(int err);
void	free_map(char **map);

#endif
