/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 19:14:03 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	get_color(t_color *color, char *s)
{
	int i;
	char **tab;

	i = 0;
	while (!ft_isdigit(s[i]))
		i++;
	if(!(tab = ft_split(s + i, ',')))
		return (MALLOC_FAIL);
	if (tab_size(tab) == 3)
	{
		color->rgb.r = ft_atoi(tab[0]);
		color->rgb.g = ft_atoi(tab[1]);
		color->rgb.b = ft_atoi(tab[2]);
		color->rgb.a = 0x00;
	}
	else 
	{
		ft_tabdel((void **)tab);
		return (WRONG_INPUT);
	}
	ft_tabdel((void **)tab); 
	return (SUCCESS);
}
