/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:19:05 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/13 14:01:55 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && i <= n)
	{
		i++;
	}
	if (s1[i] != s2[i])
	{
		return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	}
	return (0);
}