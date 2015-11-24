/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 16:38:04 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/13 13:46:29 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

int				change_oldpwd(t_uenv **env)
{
	t_uenv	*oldpwd;
	t_uenv	*tmp;

	tmp = *env;
	oldpwd = *env;
	tmp->pwd = ft_strdup((*env)->pwd);
	oldpwd->oldpwd = ft_strdup((*env)->oldpwd);
	if (!tmp || !oldpwd || !tmp->pwd || !oldpwd->oldpwd)
		return (0);
	free(oldpwd->oldpwd);
	oldpwd->oldpwd = ft_strdup(tmp->pwd);
	return (1);
}

int				check_error(char *new_path, char *path, t_uenv *env)
{
	if (chdir(new_path) == 0 && access(new_path, R_OK) != 0)
	{
		ft_putendl_fd(ft_strjoin("cd: ", ft_strjoin(path, " permission denied")), env->cs);
		return (0);
	}
	if (chdir(new_path) != 0)
	{
		ft_putendl_fd(ft_strjoin("cd: no such file or directory: ", path), env->cs);
		return (0);
	}
	if (chdir(new_path) == 0 && strncmp(getcwd(ft_strnew(1024), 1024), env->home, ft_strlen(env->home)) != 0)
	{
		ft_putendl_fd("cd: path incorrect - out of limit", env->cs);
		chdir(env->pwd);
		return (0);
	}
	//chdir(env->oldpwd);
	return (1);
}

int				check_path_spe(char *path, t_uenv *env)
{
	char	*str;

	str = ft_strdup(path);
	if (check_error(str, path, env))
		return (1);
	return (0);
}

int				check_path(t_uenv *env, char *path)
{
	t_uenv	*tmp;
	char	*str;

	tmp = env;
	tmp->pwd = ft_strdup(env->pwd);
	if (tmp == NULL)
		return (1);
	str = ft_strdup(tmp->pwd);
	str = ft_strjoin(tmp->pwd, ft_strjoin("/", path));
	if (check_error(str, path, env))
		return (1);
	return (0);
}
