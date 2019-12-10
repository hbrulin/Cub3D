/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:41:58 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/08 14:32:11 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		s_len;
	char	*dst;

	s_len = ft_strlen(s1);
	if (!(dst = (char *)malloc(sizeof(char) * s_len + 1)))
		return (NULL);
	ft_strcpy(dst, s1);
	dst[s_len] = '\0';
	return (dst);
}
