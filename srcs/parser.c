/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nponchon <nponchon@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:15:12 by nponchon          #+#    #+#             */
/*   Updated: 2024/10/30 10:15:21 by nponchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../libft/libft.h"

/*	Slight variation of ft_strnstr to look for *.fdf files only		*/

int	check_extension(char *file)
{
	int		i;
	int		j;
	char	*extension;

	i = 0;
	j = 0;
	extension = ".fdf";
	while (file[i])
	{
		if (file[i] == extension[j])
		{
			while (file[i + j] == extension[j])
			{
				if (file[i + j + 1] == '\0'
					&& extension[j + 1] == '\0')
					return (1);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

/*	This function allocates an array of strings to put each line read by GNL
	from the .fdf file.		*/

char	**get_content(int fd)
{
	int		i;
	char	*line;
	char	**content;

	i = 0;
	content = (char **)malloc(sizeof(char *) * (1000 + 1));
	if (!content)
		print_error(ENOMEM);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		content[i++] = ft_strdup(line);
		free(line);
	}
	if (content[0] == NULL)
	{
		free_array(content);
		print_error(EBADF);
	}
	content[i] = '\0';
	return (content);
}

char	**check_input(char *file)
{
	char	**map;
	int		fd;

	if (!check_extension(file))
		print_error(EINVAL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(EBADF);
	map = get_content(fd);
	close(fd);
	return (map);
}
