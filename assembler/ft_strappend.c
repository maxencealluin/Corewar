/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 12:05:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/04/24 12:09:52 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strappend(char *str, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	if (!(str = (char*)realloc(sizeof(char) * (i + ft_strlen(ext) + 1))))
		return (1);
	j = -1;
	while (ext[++j])
		str[++i - 1] = ext[j];
	str[i] = 0;
	return (0);
}
