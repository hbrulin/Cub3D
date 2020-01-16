/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:48:09 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 17:57:44 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

char	*ft_realloc(char *src)
{
	char *dst;
	if(!(dst = ft_strdup(src)))
		return (NULL);
	free(src);
	return(dst);
}

size_t tab_size(char **tab)
{
	size_t i; 
	i = 0;
	while (tab[i])
		i++;
	return(i);
}

char	*ft_strcpy_no_space(char *dst, const char *src)
{
	int i;
	int j;
	int len;

	len = ft_strlen(src);
	i = 0;
	j = 0;
	while (i <= len)
	{
		if (src[i] != ' ')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	return (dst);
}

char	*ft_strdup_no_space(const char *s)
{
	int		s_len;
	char	*dst;
	int i;
	int count;

	i = 0;
	count = 0;
	while(s[i])
	{
		if (s[i] == ' ')
			count++;
		i++;
	}
	s_len = ft_strlen(s) - count;
	if (!(dst = (char *)malloc(sizeof(char) * s_len + 1)))
		return (NULL);
	ft_strcpy_no_space(dst, s);
	dst[s_len] = '\0';
	return (dst);
}
