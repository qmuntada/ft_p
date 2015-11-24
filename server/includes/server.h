/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/18 14:06:43 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 16:20:47 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "../../libft/libft.h"
# include <stdio.h>

typedef struct			s_uenv
{
	char				*pwd;
	char				*home;
	char				*path;
	char				*oldpwd;
	int					cs;
	struct s_uenv		*next;
}						t_uenv;

int					change_oldpwd(t_uenv **env);
int					check_error(char *new_path, char *path, t_uenv *env);
int					check_path_spe(char *path, t_uenv *env);
int					check_path(t_uenv *env, char *path);
void				change_pwd(t_uenv **env);
void				cd_home(t_uenv **env);
void				cd_env_old(t_uenv **env);
void				ft_cd(t_uenv **env, char **param);
void				env_push_back(t_uenv **list, int cs);
char				**check_exec_param(t_uenv *env, char **param);
t_uenv				*core(t_uenv *env, char *line);
void				exec_core(t_uenv *env, char **param);
void				file_get(t_uenv *env, char *line);
t_uenv				*env_new(int cs);
void				file_put(t_uenv *user, char *data);


#endif
