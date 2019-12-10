/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:43:58 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/12 17:07:51 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_boucle(char const *s1, char const *s2, char *s3)
{
	int		i;
	int		j;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	i = 0;
	j = 0;
	while (s1len--)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2len--)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1len;
	size_t	s2len;

	if (!(s1 && s2))
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(s3 = (char *)malloc(sizeof(*s3) * (s1len + s2len + 1))))
		return (NULL);
	return (ft_boucle(s1, s2, s3));
}
