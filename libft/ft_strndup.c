/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmuntada <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/02 12:39:41 by qmuntada          #+#    #+#             */
/*   Updated: 2015/07/02 12:39:42 by qmuntada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(char *str, int n)
{
	char *dst;

	dst = (char *)malloc(sizeof(char) * n + 1);
	dst = ft_strncpy(dst, str, n);
	dst[n] = '\0';
	return (dst);
}
