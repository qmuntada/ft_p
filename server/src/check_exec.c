/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/12 17:09:59 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 11:14:39 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

char			**check_exec_param(t_uenv *env, char **param)
{
	t_uenv		*tmp;
	int			i;

	i = 0;
	while (param[i])
	{
		tmp = env;
		if (ft_strcmp(param[i], "$HOME") == 0)
			param[i] = ft_strdup(tmp->home);
		else if (ft_strcmp(param[i], "$OLDPWD") == 0)
			param[i] = ft_strdup(tmp->oldpwd);
		else if (ft_strcmp(param[i], "$PWD") == 0)
			param[i] = ft_strdup(tmp->pwd);
		i++;
	}
	return (param);
}
