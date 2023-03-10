/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmartine <zmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:34:37 by zmartine          #+#    #+#             */
/*   Updated: 2023/03/10 10:36:51 by zmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_read_left_str(int fd, char *left_str)
{
	char	*buff;
	int		nr_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	nr_bytes = 1;
	while (!ft_strchr(left_str, '\n') && nr_bytes != 0)
	{
		nr_bytes = read(fd, buff, BUFFER_SIZE);
		if (nr_bytes == -1)
		{
			free(left_str);
			free(buff);
			return (NULL);
		}
		buff[nr_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = ft_read_left_str(fd, left_str);
	if (!left_str)
		return (NULL);
	line = ft_get_line(left_str);
	left_str = ft_new_left_str(left_str);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("multiple_nlx5.txt", O_RDONLY);
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("Linea: %s\n", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	return (0);
// }
