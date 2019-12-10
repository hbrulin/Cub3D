/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:47:15 by hbrulin           #+#    #+#             */
/*   Updated: 2019/11/12 12:12:19 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_fill_char(int n, char *s, int i)
{
	int		tmp;

	i--;
	if (n < 0)
	{
		tmp = -n;
		s[0] = '-';
	}
	else
		tmp = n;
	if (tmp >= 10)
	{
		ft_fill_char((tmp / 10), s, i);
		s[i] = ((tmp % 10) + '0');
	}
	else
		s[i] = (tmp + '0');
	return (s);
}

int		ft_size(int n)
{
	int		size;
	int		tmp;

	size = 0;
	if (n < 0)
	{
		tmp = -n;
		size++;
	}
	else
		tmp = n;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	char	*number;

	if (n == -2147483648)
	{
		number = ft_strdup("-2147483648");
		return (number);
	}
	if (!n)
		return (ft_strdup("0"));
	size = ft_size(n);
	if (n == 0)
	{
		if (!(number = (char *)malloc(sizeof(*number) * 1)))
			return (NULL);
		number[0] = '0';
	}
	else
	{
		if (!(number = (char *)malloc(sizeof(*number) * size + 1)))
			return (NULL);
		number = ft_fill_char(n, number, size);
	}
	number[size] = '\0';
	return (number);
}
