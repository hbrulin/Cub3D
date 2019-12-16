/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 10:57:35 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		ft_parser(t_map *map)
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
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
		}
		j++;
	}
	j = 0;
	while (map->tab_map[map->nb_line - 1][j])
	{
		if (map->tab_map[map->nb_line - 1][j] != '1' && map->tab_map[map->nb_line - 1][j] != ' ')
		{
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
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
				ft_putstr("The map contains undefined characters\n");
				return (WRONG_MAP);
			}
			if (flag_n == 1 && (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W'))
			{
				ft_putstr("Player pops more than once\n");
				return (WRONG_MAP);
			}
			if (flag_n == 0 && (map->tab_map[i][j] == 'N' || map->tab_map[i][j] == 'S' || map->tab_map[i][j] == 'E' || map->tab_map[i][j] == 'W'))
				flag_n = 1;
			j++;
		}
		if (map->tab_map[i][0] != '1' || map->tab_map[i][k - 1] != '1')
		{
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
		}
		i++;
	}
	if ((k_total % (map->nb_line + 1) != 0) || flag_n == 0)
	{
		ft_putstr("The map is uneven\n");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int		ft_read(t_map *map, int fd)
{
	int 	ret;
	char *line;
	t_list	*tmp;

	map->list = NULL;
	while ((ret = get_next_line(fd, &line)) > 0) //gnl a securiser malloc, peut return MALLOC FAIL -> revoir GNL + cette ligne
	{
		if (line[0] == 'R')
			map->R = ft_strdup(line);
		if (line[0] == 'N' && line[1] == 'O')
			map->NO = ft_strdup(line);
		if (line[0] == 'S' && line[1] == 'O')
			map->SO = ft_strdup(line);
		if (line[0] == 'W' && line[1] == 'E')
			map->WE = ft_strdup(line);
		if (line[0] == 'E' && line[1] == 'A')
			map->EA = ft_strdup(line);
		if (line[0] == 'S' && line[1] == ' ')
			map->S = ft_strdup(line);
		if (line[0] == 'F' && line[1] == ' ')
			map->F = ft_strdup(line);
		if (line[0] == 'C' && line[1] == ' ')
			map->C = ft_strdup(line);
		else if (ft_isdigit(line[0]))
		{
			tmp = malloc(sizeof(t_list));
			tmp->content = ft_strdup(line);
			tmp->next = 0;
			ft_lstadd_back(&map->list, tmp);
		}
		free(line);
	}
	free(line);
	if (!map->R || !map->NO || !map->SO || !map->WE || !map->EA || !map->S || !map->F || !map->C || !map->list)
	{
		ft_putstr("Missing element");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int		get_map(t_map *map, char *file)
{
	int fd;
	t_list	*tmp;
	int i;
	int error;

	fd = open(file, O_RDONLY);
	if((error = ft_read(map, fd)) != SUCCESS)
		return(error);
	close(fd);
	if (!(map->tab_map = (char**)malloc(sizeof(char *) * ft_lstsize(map->list) + 1)))
			return (MALLOC_FAIL);
	i = 0;
	tmp = map->list;
	while (tmp)
	{
		if(!(map->tab_map[i] = ft_strdup(tmp->content)))
			return (MALLOC_FAIL);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&map->list, free);
	map->tab_map[i] = 0;
	map->nb_line = i;
	return (SUCCESS);
}
