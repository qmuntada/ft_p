/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 17:39:11 by qmuntada          #+#    #+#             */
/*   Updated: 2015/10/16 16:25:55 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <dirent.h>


void	file_get(t_uenv *env, char *line)
{
	(void)env;
	int		fd;
	char	**param;

	param = ft_strsplit(line, ' ');

	if (param[2] != NULL)
	{
		printf("Error -> Too many arguments\n");
		send(env->cs, "FAILURE\n", 8, 0);
		return;
	}
	if ((fd = open(param[1], O_RDONLY)) < 0)
	{
		printf("Error -> File not found\n");
		send(env->cs, "FAILURE\n", 8, 0);
		return ;
	}

	DIR				*dir;
	struct dirent	*dirent;

	if ((dir = opendir(".")))
	{
		while ((dirent = readdir(dir)))
		{
			if (ft_strcmp(dirent->d_name, param[1]) == 0)
			{
				if (dirent->d_type == DT_DIR)
				{
					printf("Error -> You can't copy a directory\n");
					send(env->cs, "FAILURE\n", 8, 0);
					close(fd);
					closedir(dir);
					return ;
				}
			}
		}
	}
	closedir(dir);
	int		length;
	char	*addr;
	struct stat sb;

	if (fstat(fd, &sb) == -1)
	{
		printf("Error -> Protected file\n");
		send(env->cs, "FAILURE\n", 8, 0);
		close(fd);
		return ;
	}
	length = sb.st_size;
	addr = mmap(0, length, PROT_READ, MAP_PRIVATE, fd, 0);
	char	*str = ft_strjoin(ft_itoa(length), "\n");
	send(env->cs, "SUCCESS\n", 8, 0);
	send(env->cs, str, ft_strlen(str), 0);
	send(env->cs, addr, length, 0);
	close(fd);
}

void	file_put(t_uenv *user, char *data)
{
	char	*line;
	int		fd;
	char	buff[1024];
	int		r;

	if ((get_next_line(user->cs, &line)) > 0)
	{
		write(1, line, ft_strlen(line));
		if (ft_strncmp(line, "FAILURE", 7) == 0)
		{
			write(1, "Error -> Could not open or create the file\n", 43);
		}
		else if (ft_strncmp(line, "SUCCESS", 7) == 0)
		{
			if ((fd = open(data, O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
				write(1, "Error -> Could not open or create the file\n", 43);
			else
			{
				ft_bzero(buff, 1024);
				int		b = 0;
				if ((get_next_line(user->cs, &line)) > 0)
					b = ft_atoi(line);
				int		maxsize = 0;
				ft_bzero(buff, 1024);
				while ((r = recv(user->cs, buff, 1024, 0)) > 0)
				{
					maxsize += r;
					buff[r] = '\0';
					write(fd, buff, r);
					ft_bzero(buff, 1024);
					if (maxsize >= b)
						break;
				}
			}
			close(fd);
		}
	}
}
