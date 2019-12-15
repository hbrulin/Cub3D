/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 16:01:23 by hbrulin          ###   ########.fr       */
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

t_list	*ft_read(t_map *map, int fd)
{
	int 	ret;
	char *line;
	t_list	*list;
	t_list	*tmp;

	list = NULL;
	while ((ret = get_next_line(fd, &line)) > 0) //gnl a securiser malloc
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
			ft_lstadd_back(&list, tmp);
			map->nb_line++;
		}
		free(line);
	}
	free(line);
	close(fd);
	return (list);
}

void	get_map(t_map *map, char *file)
{
	int fd;
	t_list	*list;
	t_list	*tmp;
	int i;

	fd = open(file, O_RDONLY);
	list = ft_read(map, fd);
	if (!(map->tab_map = (char**)malloc(sizeof(char *) * ft_lstsize(list) + 1)))
			return ;
	i = 0;
	tmp = list;
	while (tmp)
	{
		map->tab_map[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	//ft_lstclear(&list, del); il faut free la liste
	map->tab_map[i] = 0;
}
