/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/18 13:59:18 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 16:21:14 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <server.h>

void		usage(char *str)
{
	printf("Usage: %s <port>\n", str);
	exit(-1);
}

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sino;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sino.sin_family = AF_INET;
	sino.sin_port = htons(port);
	sino.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sock, (const struct sockaddr *)&sino, sizeof(sino)) == -1)
	{
		printf("Bind error\n");
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

int		ft_command(char *data, t_uenv *user, char *pwd)
{
	int			wt;
	char		**param;

	if (data[0] == '\0')
	{
		send(user->cs, "Wrong command\n", 14, 0);
		send(user->cs, "ERROR\n", 6, 0);
		return (1);
	}
	param = ft_split_whitespaces(data);
	wt = 300;
	(void)pwd;
	if (ft_strcmp(param[0], "ls") == 0)
	{
		user = core(user, data);
		send(user->cs, "SUCCES\n", 7, 0);
		return (1);
	}
	else if (ft_strcmp(param[0], "cd") == 0)
	{
		ft_cd(&user, ft_strsplit(data, ' '));
		//send(user->cs, ft_strjoin(user->pwd, "\n"), ft_strlen(user->pwd) + 1, 0);
		send(user->cs, "SUCCES\n", 7, 0);
		return (1);
	}
	else if (ft_strcmp(param[0], "get") == 0)
	{
		file_get(user, data);
		//send(user->cs, "SUCCES\n", 7, 0);
		return (1);
	}
	else if (ft_strcmp(param[0], "put") == 0)
	{
		file_put(user, param[1]);
		//send(user->cs, "SUCCES\n", 7, 0);
		return (1);
	}
	else if (ft_strcmp(param[0], "pwd") == 0 && param[1] == NULL)
	{
		send(user->cs, ft_strjoin(user->pwd, "\n"), ft_strlen(user->pwd) + 1, 0);
		send(user->cs, "SUCCES\n", 7, 0);
		return (1);
	}
	else if (ft_strcmp(param[0], "quit") == 0 && param[1] == NULL)
	{
		send(user->cs, "Exit\n", 5, 0);
		close(user->cs);
		return (0);
	}
	else
	{
		send(user->cs, "Wrong command\n", 14, 0);
		send(user->cs, "ERROR\n", 6, 0);
	}
	return (1);
}

static void		fork_child(t_uenv	*user)
{
	int							ret;
	char						pwd[4096];
	char						data[1024];

	getcwd(pwd, 4096);
	while (42)
	{
		if ((ret = recv(user->cs, data, 1024, 0)) > 0)
		{
			data[ret - 1] = '\0';
			printf("[%d] \x1B[33mreceived %d bytes: [%s]\x1B[0m\n",
					user->cs, ret, data);
			if (ft_command(data, user, pwd) == 0)
				return ;
			ft_strclr(data);
		}
		else
			break;
		ret = 0;
	}
	close (user->cs);
}

int main(int argc, char **argv)
{
	int						port;
	int						sock;
	int						cs;
	unsigned int			cslen;
	struct sockaddr_in		csin;
	t_uenv					*user;
	pid_t					parent;
	
	user = NULL;
	if (argc != 2)
		usage(argv[0]);
	port = ft_atoi(argv[1]);
	sock = create_server(port);
	while ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)))
	{
		if ((parent = fork()) == -1)
		{
			return (0);
		}
		if (!parent)
		{
			printf("[\x1B[32mO\x1B[0m] New user [%d] connected\n", cs);
			env_push_back(&user, cs);
			fork_child(user);
			printf("[\x1B[31mX\x1B[0m] User [%d] disconnected\n", cs);
			close(cs);
			return(0);
		}
	}
	if (cs == -1)
		printf("Socket error\n");
	close (cs);
	close (sock);
	return 0;
}
