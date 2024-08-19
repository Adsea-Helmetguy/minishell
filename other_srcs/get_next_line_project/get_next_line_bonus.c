/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:54:49 by mlow              #+#    #+#             */
/*   Updated: 2023/10/13 17:29:50 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft_project/libft.h"

static char	*line_ext(char *stored_data)
{
	int		index;
	char	*line_read;

	index = 0;
	while (stored_data[index] && stored_data[index] != '\n')
		index++;
	line_read = (char *)malloc((index + 2) * (sizeof(char)));
	if (!line_read)
		return (NULL);
	index = 0;
	while (stored_data[index] && stored_data[index] != '\n')
	{
		line_read[index] = stored_data[index];
		index++;
	}
	if (stored_data[index] == '\n')
	{
		line_read[index] = '\n';
		index++;
	}
	line_read[index] = '\0';
	return (line_read);
}

static char	*ft_static_line(char *str)
{
	unsigned int	num_s;
	unsigned int	num_st;
	char			*new_str;

	num_s = 0;
	while (str[num_s] && str[num_s] != '\n')
		num_s++;
	if (!str[num_s])
		return (ft_free(&str));
	new_str = (char *)malloc((ft_strlen2(str) - num_s + 1) * (sizeof(char)));
	if (!new_str)
		return (NULL);
	if (str[num_s] == '\n')
		num_s++;
	num_st = 0;
	while (str[num_s + num_st])
	{
		new_str[num_st] = str[num_s + num_st];
		num_st++;
	}
	new_str[num_st] = '\0';
	ft_free(&str);
	return (new_str);
}

static char	*bufstored_data(int fd, char *stored_data)
{
	char		*buf;
	ssize_t		bytes_read;

	buf = (char *)malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr2(stored_data, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			ft_free(&stored_data);
			return (ft_free(&buf));
		}
		buf[bytes_read] = '\0';
		stored_data = str_combined(buf, stored_data);
	}
	ft_free(&buf);
	return (stored_data);
}

char	*get_next_line(int fd)
{
	static char	*stored_data[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!stored_data[fd])
	{
		stored_data[fd] = (char *)malloc((1) * sizeof(char));
		if (!stored_data[fd])
			return (NULL);
		*stored_data[fd] = '\0';
	}
	stored_data[fd] = bufstored_data(fd, stored_data[fd]);
	if (!stored_data[fd])
		return (ft_free(&stored_data[fd]));
	line = line_ext(stored_data[fd]);
	if (!line || !line[0])
	{
		ft_free(&stored_data[fd]);
		return (ft_free(&line));
	}
	stored_data[fd] = ft_static_line(stored_data[fd]);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	char	*buf = NULL;
	
	fd = open("./file.txt", O_RDONLY);
	fd1 = open("./epic.txt", O_RDONLY);
	fd2 = open("./empty.txt", O_RDONLY);
	while ((buf = get_next_line(fd)) != NULL)
	{
		printf("\nStatic line: %s\n", buf);
		free(buf);
	}
	printf("\nStatic line: %s\n", buf);
	printf("\nStatic line: %s\n", buf);
	while ((buf = get_next_line(fd1)) != NULL)
	{
		printf("\nStatic line: %s\n", buf);
		free(buf);
	}
	printf("\nStatic line: %s\n", buf);
	printf("\nStatic line: %s\n", buf);
	while ((buf = get_next_line(fd2)) != NULL)
	{
		printf("\nStatic line: %s\n", buf);
		free(buf);
	}
	printf("\nStatic line: %s\n", buf);
	printf("\nStatic line: %s\n", buf);
	close(fd);
	close(fd1);
	close(fd2);
	return (0);
}
*/
