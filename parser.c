/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/17 15:25:29 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
◦ Mis à part la description de la map, chaque type d’élément peut être séparée par une ou plusieurs lignes vides.
◦ La description de la carte sera toujours en dernier dans le fichier, le reste des éléments peut être dans n’importe quel ordre.
◦ Les informations de chaque élément peuvent être séparées par un ou plusieurs espace(s).*/

int		ft_parser(t_env *env)
{
	int i;
	int j;
	int k;
	int k_total;
	int flag_n;

	j = 0;
	k_total = ft_strlen(env->map.tab_map[0]) + ft_strlen(env->map.tab_map[env->map.nb_line - 1]);

	while (env->map.tab_map[0][j])
	{
		if (env->map.tab_map[0][j] != '1' && env->map.tab_map[0][j] != ' ')
		{
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
		}
		j++;
	}
	j = 0;
	while (env->map.tab_map[env->map.nb_line - 1][j])
	{
		if (env->map.tab_map[env->map.nb_line - 1][j] != '1' && env->map.tab_map[env->map.nb_line - 1][j] != ' ')
		{
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
		}
		j++;
	}

	i = 1;
	j = 1;
	flag_n = 0;
	while (env->map.tab_map[i] && i < env->map.nb_line)
	{
		k = ft_strlen(env->map.tab_map[i]);
		k_total += k;
		j = 1;
		while (env->map.tab_map[i][j])
		{
			if (!(env->map.tab_map[i][j] == '1' || env->map.tab_map[i][j] == '0' || env->map.tab_map[i][j] == '2' || env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W' || env->map.tab_map[i][j] == ' '))
			{
				ft_putstr("The map contains undefined characters\n");
				return (WRONG_MAP);
			}
			if (flag_n == 1 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
			{
				ft_putstr("Player pops more than once\n");
				return (WRONG_MAP);
			}
			if (flag_n == 0 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
			{
				flag_n = 1;
				env->map.player = env->map.tab_map[i][j];
				env->map.tab_pos[0] = j; //x
				env->map.tab_pos[1] = i; //y
			}
			j++;
		}
		if (env->map.tab_map[i][0] != '1' || env->map.tab_map[i][k - 1] != '1')
		{
			ft_putstr("The map is not closed\n");
			return (WRONG_MAP);
		}
		i++;
	}
	if ((k_total % (env->map.nb_line + 1) != 0) || flag_n == 0)
	{
		ft_putstr("The map is uneven\n");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int		ft_read(t_env *env, t_data *data, int fd)
{
	int 	ret;
	char *line;
	t_list	*tmp;

	env->map.list = NULL;
	env->map.tab_map = NULL; //necessaire??
	while ((ret = get_next_line(fd, &line)) > 0) //gnl a securiser malloc, peut return MALLOC FAIL -> revoir GNL + cette ligne
	{
		if (line[0] == 'R')
			data->R = ft_strdup(line);
		if (line[0] == 'N' && line[1] == 'O')
			data->NO = ft_strdup(line);
		if (line[0] == 'S' && line[1] == 'O')
			data->SO = ft_strdup(line);
		if (line[0] == 'W' && line[1] == 'E')
			data->WE = ft_strdup(line);
		if (line[0] == 'E' && line[1] == 'A')
			data->EA = ft_strdup(line);
		if (line[0] == 'S' && line[1] == ' ')
			data->S = ft_strdup(line);
		if (line[0] == 'F' && line[1] == ' ')
			data->F = ft_strdup(line);
		if (line[0] == 'C' && line[1] == ' ')
			data->C = ft_strdup(line);
		else if (ft_isdigit(line[0]))
		{
			tmp = malloc(sizeof(t_list));
			tmp->content = ft_strdup(line);
			tmp->next = 0;
			ft_lstadd_back(&env->map.list, tmp);
		}
		free(line);
	}
	free(line);
	if (!data->R || !data->NO || !data->SO || !data->WE || !data->EA || !data->S || !data->F || !data->C || !env->map.list)
	{
		ft_putstr("Missing element");
		return (WRONG_MAP);
	}
	return (SUCCESS);
}

int		get_map(t_env *env, t_data *data, char *file)
{
	int fd;
	t_list	*tmp;
	int i;
	int error;

	fd = open(file, O_RDONLY);
	if((error = ft_read(env, data, fd)) != SUCCESS)
		return(error);
	close(fd);
	if (!(env->map.tab_map = (char**)malloc(sizeof(char *) * ft_lstsize(env->map.list) + 1)))
			return (MALLOC_FAIL);
	i = 0;
	tmp = env->map.list;
	while (tmp)
	{
		if(!(env->map.tab_map[i] = ft_strdup(tmp->content)))
			return (MALLOC_FAIL);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&env->map.list, free);
	env->map.tab_map[i] = 0;
	env->map.nb_line = i;
	return (SUCCESS);
}
