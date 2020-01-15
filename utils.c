/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 13:48:09 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/15 14:29:53 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3D.h"

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
