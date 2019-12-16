/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 16:10:48 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int hex = (0 << 24) | ((unsigned char)r << 16) | ((unsigned char)g << 8) | ((unsigned char)b<<0); 
	printf("%u", hex);
	return(hex);
}

void	color_floor_ceiling(t_env *env, t_color *colors)
{
	// ya til erreur a checker ici?
	colors->color_floor = mlx_get_color_value (env->mlx_ptr, rgb_to_hex(colors->r_floor, colors->g_floor, colors->b_floor));
	colors->color_ceiling = mlx_get_color_value (env->mlx_ptr, rgb_to_hex(colors->r_ceiling, colors->g_ceiling, colors->b_ceiling));
}

int	get_rgb(t_env *env, t_map *map, t_color *colors)
{
	int i;
	char **tab;

	i = 0;
	while (!ft_isdigit(map->F[i]))
		i++;
	if(!(tab = ft_split(map->F + i, ',')))
		return (MALLOC_FAIL);
	colors->r_floor = ft_atoi(tab[0]);
	colors->g_floor= ft_atoi(tab[1]);
	colors->b_floor= ft_atoi(tab[2]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel
	if ((!colors->r_floor && colors->r_floor != 0) || (!colors->g_floor && colors->g_floor != 0) || (!colors->b_floor && colors->b_floor != 0)) //autre chose a verifier quand a mauvais input (genre si pas de virgule entre les valeurs dans le doc map)
	{
		ft_putstr("Wrong floor color");
		return (WRONG_INPUT);
	}

	i = 0;
	while (!ft_isdigit(map->C[i]))
		i++;
	if(!(tab = ft_split(map->C + i, ',')))
		return (MALLOC_FAIL);
	colors->r_ceiling = ft_atoi(tab[0]);
	colors->g_ceiling = ft_atoi(tab[1]);
	colors->b_ceiling= ft_atoi(tab[2]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel
	if ((!colors->r_ceiling && colors->r_ceiling!= 0) || (!colors->g_ceiling && colors->g_ceiling != 0) || (!colors->b_ceiling && colors->b_ceiling != 0))//autre chose a verifier quand a mauvais input (genre si pas de virgule entre les valeurs dans le doc map)
	{
		ft_putstr("Wrong ceiling color");
		return (WRONG_INPUT);
	}
	color_floor_ceiling(env, colors);
	return (SUCCESS);
}
