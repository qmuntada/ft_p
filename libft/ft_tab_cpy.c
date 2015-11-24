/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_cpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:40:09 by qmuntada          #+#    #+#             */
/*   Updated: 2015/07/02 12:40:20 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tab_cpy(char **tab)
{
	int			i;
	char		**new_tab;

	i = -1;
	new_tab = (char **)malloc(sizeof(char *) * tab_lenght(tab) + 1);
	while (tab[++i])
		new_tab[i] = ft_strdup(tab[i]);
	new_tab[i] = NULL;
	return (new_tab);
}
