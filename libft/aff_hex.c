/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_hex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 10:55:42 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/08 10:59:12 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		conv_hex(int nb)
{
	if (nb <= 9)
		return (nb + '0');
	return (nb - 10 + 'a');
}

char	*aff_hex(unsigned long value)
{
	char			*str;
	int				n;
	unsigned long	nb;

	nb = value;
	n = 0;
	while (nb >= 16)
	{
		nb = nb / 16;
		n++;
	}
	if (!(str = (char *)malloc((n + 1) * sizeof(str))))
		return (NULL);
	if (str)
	{
		str[n + 1] = '\0';
		while (n >= 0)
		{
			nb = value % 16;
			str[n] = conv_hex(nb);
			value = value / 16;
			n--;
		}
	}
	return (str);
}
