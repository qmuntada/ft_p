/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_lenght.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:40:27 by qmuntada          #+#    #+#             */
/*   Updated: 2015/07/02 12:40:28 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			tab_lenght(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
