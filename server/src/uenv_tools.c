/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uenv_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frcugy <frcugy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 16:25:22 by frcugy            #+#    #+#             */
/*   Updated: 2015/10/16 13:15:09 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

t_uenv		*env_new(int cs)
{
	t_uenv			*new;
	char			pwd[4096];

	getcwd(pwd, 4096);
	new = (t_uenv*)malloc(sizeof(t_uenv));
	new->cs = cs;
	new->pwd = ft_strdup(pwd);
	new->oldpwd = ft_strdup(pwd);
	new->home = ft_strdup(pwd);
	new->next = NULL;
	return (new);
}

void	env_push_back(t_uenv **list, int cs)
{
	t_uenv	*new;

	new = *list;
	if (new)
	{
		while (new->next)
		{
			new = new->next;
		}
		new->next = env_new(cs);
	}
	else
	{
		*list = env_new(cs);
	}
}
