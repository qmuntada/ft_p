/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 17:10:06 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 11:14:57 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

t_uenv			*core(t_uenv *env, char *line)
{
	char		**param;

	param = ft_split_whitespaces(line);
	exec_core(env, param);
	return (env);
}

void			exec_core(t_uenv *env, char **param)
{
	char		*exec;

	exec = "/bin/ls";
	param = check_exec_param(env, param);
	if (!fork())
	{
		dup2(env->cs, 1);
		dup2(env->cs, 2);
		if (param)
			execv(exec, param);
		exit(0);
	}
	else
		wait(0);
}

void			exec_core2(t_uenv *env, char **param)
{
	char		*exec;

	exec = "/bin/touch";
	if (!fork())
	{
		dup2(env->cs, 1);
		dup2(env->cs, 2);
		if (param)
			execv(exec, param);
		exit(0);
	}
	else
		wait(0);
}
