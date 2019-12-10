/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/10 13:35:01 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_parser(t_map *map, char *file)
{
	int 	ret;
	int i;
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (!(map->tab_map = (char**)malloc(sizeof(char *) * map->nb_line))) //voir pour le +1
			return ;
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		map->tab_map[i] = ft_strdup(line);
		i++;
	}
	//map->tab_map[i] = "\0"; //pourquoi je ne peux pas mettre ca a la fin de mon char **
}
