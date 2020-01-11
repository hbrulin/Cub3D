/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 18:31:32 by hbrulin          ###   ########.fr       */
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
	int flag_sp;

	j = 0;
	flag_sp = 0;
	k_total = ft_strlen(env->map.tab_map[0]) + ft_strlen(env->map.tab_map[env->map.nb_line - 1]);

	while (env->map.tab_map[0][j])
	{
		if (env->map.tab_map[0][j] != '1' && env->map.tab_map[0][j] != ' ')
			return (WRONG_MAP);
		j++;
	}
	j = 0;
	while (env->map.tab_map[env->map.nb_line - 1][j])
	{
		if (env->map.tab_map[env->map.nb_line - 1][j] != '1' && env->map.tab_map[env->map.nb_line - 1][j] != ' ')
			return (WRONG_MAP);
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
				return (WRONG_MAP);
			if (flag_n == 1 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
				return (WRONG_MAP);
			if (flag_n == 0 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
			{
				flag_n = 1;
				env->map.player = env->map.tab_map[i][j];
				env->pos.x = j; //x
				env->pos.y = i; //y
			}
			//coordonees sprite, faut il return une erreur si 0 sprite, ou si plusieurs
			if (env->map.tab_map[i][j] == '2')
			{
				env->sp.pos_x = j + 0.5;
				env->sp.pos_y = i + 0.5;
				flag_sp++;
			}
			if (env->map.tab_map[i][j] == ' ')
				env->map.tab_map[i][j] = '0';
			j++;
		}
		if (env->map.tab_map[i][0] != '1' || env->map.tab_map[i][k - 1] != '1')
			return (WRONG_MAP);
		i++;
	}
	if ((k_total % (env->map.nb_line + 1) != 0) || flag_n == 0 || flag_sp != 1)
		return (WRONG_MAP);
	return (SUCCESS);
}

int		ft_read(t_env *env, int fd)
{
	int 	ret;
	char *line;
	t_list	*tmp;

	env->map.list = NULL;
	env->map.tab_map = NULL; 
	//comment securiser ca pour que ce soit a la norme??
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == 'R')
			env->data.R = ft_strdup(line);
		if (line[0] == 'N' && line[1] == 'O')
			env->data.NO = ft_strdup(line);
		if (line[0] == 'S' && line[1] == 'O')
			env->data.SO = ft_strdup(line);
		if (line[0] == 'W' && line[1] == 'E')
			env->data.WE = ft_strdup(line);
		if (line[0] == 'E' && line[1] == 'A')
			env->data.EA = ft_strdup(line);
		if (line[0] == 'S' && line[1] == ' ')
			env->data.S = ft_strdup(line);
		if (line[0] == 'F' && line[1] == ' ')
			env->data.F = ft_strdup(line);
		if (line[0] == 'C' && line[1] == ' ')
			env->data.C = ft_strdup(line);
		else if (ft_isdigit(line[0]))
		{
			if(!(tmp = malloc(sizeof(t_list))))
				return (MALLOC_FAIL);
			if(!(tmp->content = ft_strdup(line)))
				return (MALLOC_FAIL);
			tmp->next = 0;
			ft_lstadd_back(&env->map.list, tmp);
		}
		free(line);
	}
	free(line);
	if (!env->data.R || !env->data.NO || !env->data.SO || !env->data.WE || !env->data.EA || !env->data.S || !env->data.F || !env->data.C || !env->map.list)
		return (INVALID_ARG);

	//fix path, leaks ici
	int i = 0;
	while (env->data.NO[i] != '.')
		i++;
	if(!(env->data.NO = ft_strdup(env->data.NO + i)))
		return (MALLOC_FAIL);
	i = 0;
	while (env->data.SO[i] != '.')
		i++;
	if(!(env->data.SO = ft_strdup(env->data.SO + i)))
		return (MALLOC_FAIL);
	i = 0;
	while (env->data.WE[i] != '.')
		i++;
	if(!(env->data.WE = ft_strdup(env->data.WE + i)))
		return (MALLOC_FAIL);
	i = 0;
	while (env->data.EA[i] != '.')
		i++;
	if(!(env->data.EA = ft_strdup(env->data.EA + i)))
		return (MALLOC_FAIL);
	i = 0;
	while (env->data.S[i] != '.')
		i++;
	if(!(env->data.S = ft_strdup(env->data.S + i)))
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int		get_map(t_env *env, char *file)
{
	int fd;
	t_list	*tmp;
	int i;
	int error;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (OPEN_ERR);
	if((error = ft_read(env, fd)) != SUCCESS)
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
