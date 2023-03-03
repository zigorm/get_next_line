/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmartine <zmartine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:34:37 by zmartine          #+#    #+#             */
/*   Updated: 2023/03/03 13:11:32 by zmartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_new_line(char *str);

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	int			i;
	static char	*box;
	char		*line;
	char		*aux;
	int			num_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	num_read = 0;
	line = NULL;
	line = calloc(1, sizeof(char));
	if (box != NULL)
	{
		free(line);
		line = ft_strdup(box);
		free(box);
		box = NULL;
	}
	while (i == 0 || check_new_line(line) == 0)
	{
		num_read = read(fd, buf, BUFFER_SIZE);
		if (num_read <= 0)
			break ;
		buf[num_read] = '\0';
		aux = ft_strdup(line);
		free(line);
		line = ft_strjoin(aux, buf);
		free(aux);
		i++;
	}
	aux = ft_strdup(line);
	i = check_new_line(aux);
	if (i != 0)
	{
		line[i + 1] = '\0';
		box = ft_strdup(aux + i + 1);
	}
	free(aux);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

/* int	main(void)
{
	int		fd;
	char	*str;

	fd = open("multiple_nlx5.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("Linea: %s\n", str);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
} */
