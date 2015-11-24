/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/18 13:59:23 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 16:28:28 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <client.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/mman.h>

void		usage(char *str)
{
	printf("Usage: %s <addr> <port>\n", str);
	exit(-1);
}

void		handler(void)
{
	close(g_sock);
	exit(0);
}

int		create_client(char *addr, int port)
{
	int					g_sock;
	struct protoent		*proto;
	struct sockaddr_in	sino;

	if (ft_strcmp("localhost", addr) == 0)
		addr = ft_strdup("127.0.0.1");
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	g_sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sino.sin_family = AF_INET;
	sino.sin_port = htons(port);
	sino.sin_addr.s_addr = inet_addr(addr);
	if (connect(g_sock, (const struct sockaddr *)&sino, sizeof(sino)) == -1)
	{
		printf("Connection error\n");
		exit(2);
	}
	return (g_sock);
}

void	put_file(char *name)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		printf("Error -> File not found\n");
		send(g_sock, "FAILURE\n", 8, 0);
		return ;
	}

	DIR*dir;
	struct dirent*dirent;

	if ((dir = opendir(".")))
	{
		while ((dirent = readdir(dir)))
		{
			if (ft_strcmp(dirent->d_name, name) == 0)
			{
				if (dirent->d_type == DT_DIR)
				{
					printf("Error -> You can't copy a directory\n");
					send(g_sock, "FAILURE\n", 8, 0);
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
		send(g_sock, "FAILURE\n", 8, 0);
		close(fd);
		return ;
	}
	length = sb.st_size;
	addr = mmap(0, length, PROT_READ, MAP_PRIVATE, fd, 0);
	char*str = ft_strjoin(ft_itoa(length), "\n")	;
	send(g_sock, "SUCCESS\n", 8, 0);
	send(g_sock, str, ft_strlen(str), 0);
	send(g_sock, addr, length, 0);
	close(fd);
}

int main(int argc, char **argv)
{
	int						port;
	int						r;
	char					buff[1024];
	char					*line;
	int						wt;
	char					**param;
	int						fd;

	wt = 0;
	r = 0;
	if (argc != 3)
		usage(argv[0]);
	port = ft_atoi(argv[2]);
	g_sock = create_client(argv[1], port);
	signal(SIGINT, (void(*)())handler);
	ft_putstr(C_NONE);
	ft_putstr(C_BOLD);
	ft_putstr("ft_p >> ");
	ft_putstr(C_NONE);
	ft_putstr(C_GRAY);
	while ((r = read(0, buff, 1024)) > 0)
	{
		ft_putstr(C_NONE);
		ft_putstr(C_GREEN);
		buff[r] = '\0';
		param = ft_split_whitespaces(buff);
		send(g_sock, buff, ft_strlen(buff), 0);
		if (ft_strcmp(buff, "quit\n") == 0)
		{
			close(g_sock);
			exit(0);
		}
		ft_bzero(buff, 1024);
		if (param[0] && ft_strncmp("get", param[0], 3) == 0)
		{
			if ((get_next_line(g_sock, &line)) > 0)
			{
				write(1, line, ft_strlen(line));
				if (ft_strncmp(line, "FAILURE", 7) == 0)
				{
					write(1, "Error -> Could not open or create the file\n", 43);
				}
				else if (ft_strncmp(line, "SUCCESS", 7) == 0)
				{
					if ((fd = open(param[1], O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
						write(1, "Error -> Could not open or create the file\n", 43);
					else
					{
						ft_bzero(buff, 1024);
						int		b = 0;
						if ((get_next_line(g_sock, &line)) > 0)
							b = ft_atoi(line);
						int		maxsize = 0;
						ft_bzero(buff, 1024);
						while ((r = recv(g_sock, buff, 1024, 0)) > 0)
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
		else if (param[0] && ft_strncmp("put", param[0], 3) == 0)
		{
			if (param[1])
				put_file(param[1]);
			else
			{
				write(1, "Error -> Need a file name as second parameter\n", 43);
			}
		}
		else
		{
			while ((r = get_next_line(g_sock, &line)) > 0)
			{
				if (ft_strcmp("SUCCES", line) == 0)
				{
					write(0, "\nSUCCES\n", 8);
					break;
				}
				else if (ft_strcmp("ERROR", line) == 0)
				{
					write(0, "\nERROR\n", 7);
					break;
				}
				printf("%s\n", line);
			}
		}
		r = 0;
		ft_putstr(C_NONE);
		ft_putstr(C_BOLD);
		ft_putstr("ft_p >> ");
		ft_putstr(C_NONE);
		r = 0;
		ft_putstr(C_GRAY);
	}
	close (g_sock);
	return 0;
}
