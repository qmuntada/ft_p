/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 16:38:03 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/13 10:40:12 by frcugy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void			change_pwd(t_uenv **env)
{
	t_uenv		*tmp;

	tmp = *env;
	tmp->pwd = ft_strdup((*env)->pwd);
	if (tmp == NULL)
		return ;
	tmp->pwd = getcwd(ft_strnew(1024), 1024);
}

void			cd_home(t_uenv **env)
{
	t_uenv		*tmp1;
	t_uenv		*tmp2;

	tmp1 = *env;
	tmp2 = *env;
	tmp1->pwd = ft_strdup((*env)->pwd);
	tmp2->home = ft_strdup((*env)->home);
	if (tmp1 && tmp1->pwd && tmp2 && tmp2->home &&
		access(tmp2->home, R_OK) == 0)
	{
		free(tmp1->pwd);
		tmp1->pwd = ft_strdup(tmp2->home);
		change_oldpwd(env);
		chdir(tmp1->pwd);
	}
	else
		ft_putendl("cd: incorrect or unassigned home path");
}

void			cd_env_old(t_uenv **env)
{
	t_uenv	*tmp1;
	t_uenv	*tmp2;
	char	*oldpwd;

	tmp1 = *env;
	tmp2 = *env;
	tmp1->pwd = ft_strdup((*env)->pwd);
	tmp2->oldpwd = ft_strdup((*env)->oldpwd);
	if (tmp1 && tmp2 && access(tmp2->oldpwd, R_OK) == 0)
	{
		ft_putendl(tmp2->oldpwd);
		oldpwd = ft_strdup(tmp1->pwd);
		free(tmp1->pwd);
		tmp1->pwd = ft_strdup(tmp2->oldpwd);
		change_oldpwd(env);
		chdir(tmp1->pwd);
		free(tmp2->oldpwd);
		tmp2->oldpwd = ft_strdup(oldpwd);
		free(oldpwd);
	}
}

void			ft_cd(t_uenv **env, char **param)
{
	if (!param[1] || (param[1][0] == '~' && !param[1][1]))
		cd_home(env);
	else if (param[1][0] == '-' && !param[1][1])
		cd_env_old(env);
	else if ((param[1][0] == '/') ? check_path_spe(param[1], *env) :
	check_path(*env, param[1]))
	{
		if (change_oldpwd(env))
			change_pwd(env);
	}
}
