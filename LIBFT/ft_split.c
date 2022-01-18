/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 11:38:30 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/18 21:16:57 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_countarray(char const *s, char c)
{
	int	i;
	int	array;

	i = 0;
	array = 0;
	if (!s)
		return(0);
	while (s[i])
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
			array++;
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	array;
	size_t	start;
	char	**str;

	j = 0;
	i = 0;
	array = ft_countarray(s, c);
	str = malloc(array * sizeof(char) + 1);
	if (!str || str == 0)
		return (NULL);
	while (s[i] && j != array)
	{
		while (s[i++] == c)
			start = i;
		while (s[i] != c)
			i++;
		str[j] = malloc(i - start * sizeof(char) + 1);
		str[j++] = ft_substr(s, start, i - start);
	}
	str[j] = NULL;
	return (str);
}

int	main(void)
{
    int i = 0;
    char **tab;
        
    tab = ft_split("        ", ' ');
    while (i < 2)
    {
        printf("string %d : %s\n", i, tab[i]);
        i++;
    }
    return (0);
}
