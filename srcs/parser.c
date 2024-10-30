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

/*	This function allocates an array of strings to put each line from
	the .fdf file. Each line gets read from GNL and is trimmed from
	the \n at the end.		*/

char	**get_content(int fd)
{
	int		i;
	char	*line;
	char	**content;

	i = 0;
	content = (char **)malloc(sizeof(char*) * (COL_MAX + 1));
	if (!content)
		print_error(ENOMEM);
	content[COL_MAX] = "\0";
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		//line = ft_strtrim(line, "\n");
		content[i++] = ft_strdup(line);
		free(line);
	}
	if (content[0] == NULL)
		print_error(EBADF);
	return (content);
}

char	**check_content(char *file)
{
	int		fd;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error(EBADF);
	map = get_content(fd);
	close(fd);
	return (map);
}

void	check_input(char *file)
{
	char	**map;
	int		i;

	/*	TODO
		- open and read with GNL: check for digits and hexas only,
		minimum of 2 col, 2 rows?
	*/

	if (!check_extension(file))
		print_error(EINVAL);
	map = check_content(file);
	i = 0;
	while (map[i] != NULL)
		ft_printf("%s\n", map[i++]);
	free_map(map);
}
