/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 11:08:49 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/08 11:10:52 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	char			*s;
	unsigned int	nb;
	int				len;

	len = 1;
	nb = n;
	while (nb > 9)
	{
		nb /= 10;
		++len;
	}
	if (!(s = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	while (n > 9)
	{
		s[--len] = (n % 10) + 48;
		n /= 10;
	}
	s[--len] = n + 48;
	return (s);
}
