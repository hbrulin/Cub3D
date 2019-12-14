/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/14 20:50:41 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		check_map(t_map *map)
{
	int i;
	int j;
	int k;
	int k_total;
	int flag_n;

	j = 0;
	k_total = ft_strlen(map->tab_map[0]) + ft_strlen(map->tab_map[map->nb_line - 1]);

	while (map->tab_map[0][j])
	{
		if (map->tab_map[0][j] != '1' && map->tab_map[0][j] != ' ')
		{
			printf("%i", 1); //retirer cela partout, utiliser les return pour checker erreurs
			return (-1);
		}
		j++;
	}
	j = 0;
	while (map->tab_map[map->nb_line - 1][j])
	{
		if (map->tab_map[map->nb_line - 1][j] != '1' && map->tab_map[map->nb_line - 1][j] != ' ')
		{
			printf("%i", 2);
			return (-1);
		}
		j++;
	}

	i = 1;
	j = 1;
	flag_n = 0;
	char c;
	while (map->tab_map[i] && i < map->nb_line)
	{
		k = ft_strlen(map->tab_map[i]);
		k_total += k;
		j = 1;
		while (map->tab_map[i][j])
		{
			c = map->tab_map[i][j];
			if (!(map->tab_map[i][j] == '1' || map->tab_map[i][j] == '0' || map->tab_map[i][j] == '2' || map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W' || map->tab_map[i][j] == ' '))
			{
				printf("%i", 3);
				return (-1);
			}
			if (flag_n == 1 && (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W'))
			{
				printf("%i", 4);
				return (-1);
			}
			if (flag_n == 0 && (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W'))
				flag_n = 1;
			j++;
		}
		if (map->tab_map[i][0] != '1' || map->tab_map[i][k - 1] != '1')
		{
			printf("%i", 5);
			return (-1);
		}
		i++;
	}
	if ((k_total % (map->nb_line + 1) != 0) || flag_n == 0)
	{
		printf("%i", 6);
		return (-1);
	}
	return (0);
}

//rajouter une condition selon lauelle si pas de personnage

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
	while ((ret = get_next_line(fd, &line)) > 0) //gn a securiser malloc
	{
		map->tab_map[i] = ft_strdup(line);
		i++;
	}
	//map->tab_map[i] = "\0"; //pourquoi je ne peux pas mettre ca a la fin de mon char **
}
