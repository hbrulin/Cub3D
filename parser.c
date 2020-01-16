/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 12:42:03 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		ft_parser(t_env *env)
{
	int i;
	int j;
	int k;
	int k_total;
	int flag_n;

	j = 0;
	env->nb_sprite = 0;
	k_total = ft_strlen(env->map.tab_map[0]) + ft_strlen(env->map.tab_map[env->map.nb_line - 1]);

	while (env->map.tab_map[0][j])
	{
		if (env->map.tab_map[0][j] != '1')
			return (WRONG_MAP);
		j++;
	}
	j = 0;
	while (env->map.tab_map[env->map.nb_line - 1][j])
	{
		if (env->map.tab_map[env->map.nb_line - 1][j] != '1')
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
			if (!(env->map.tab_map[i][j] == '1' || env->map.tab_map[i][j] == '0' || env->map.tab_map[i][j] == '2' || env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
				return (WRONG_MAP);
			if (flag_n == 1 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
				return (WRONG_MAP);
			if (flag_n == 0 && (env->map.tab_map[i][j] == 'N' || env->map.tab_map[i][j] == 'S' || env->map.tab_map[i][j] == 'E' || env->map.tab_map[i][j] == 'W'))
			{
				flag_n = 1;
				env->map.player = env->map.tab_map[i][j];
				env->pos.x = j; 
				env->pos.y = i;
				env->map.tab_map[i][j] = '0';
			}
			//coordonees sprite, faut il return une erreur si 0 sprite, ou si plusieurs
			if (env->map.tab_map[i][j] == '2')
			{
				env->nb_sprite++;
				//env->sp.pos_x = j + 0.5;
				//env->sp.pos_y = i + 0.5;
			}
			j++;
		}
		if (env->map.tab_map[i][0] != '1' || env->map.tab_map[i][k - 1] != '1')
			return (WRONG_MAP);
		i++;
	}
	if ((k_total % (env->map.nb_line + 1) != 0) || flag_n == 0)
		return (WRONG_MAP);
	env->map.nb_char = k;
	return (SUCCESS);
}

int		ft_read(t_env *env, int fd)
{
	int 	ret;
	char *line;
	t_list	*tmp;
	int i;

	//comment securiser ca pour que ce soit a la norme?? faire une ft if isalpha
	while ((ret = get_next_line(fd, &line)) > 0)
	{	
		i = 0;
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] == 'R')
			env->data.R = ft_strdup(line + i);
		if (line[i] == 'N' && line[i + 1] == 'O')
			env->data.n = ft_strdup(line + i);
		if (line[i] == 'S' && line[i + 1] == 'O')
			env->data.s = ft_strdup(line + i);
		if (line[i] == 'W' && line[i + 1] == 'E')
			env->data.w = ft_strdup(line + i);
		if (line[i] == 'E' && line[i + 1] == 'A')
			env->data.e = ft_strdup(line + i);
		if (line[i] == 'S' && line[i + 1] == ' ')
			env->data.sp = ft_strdup(line + i);
		if (line[i] == 'F' && line[i + 1] == ' ')
			env->data.F = ft_strdup(line + i);
		if (line[i] == 'C' && line[i + 1] == ' ')
			env->data.C = ft_strdup(line + i);
		else if (ft_isdigit(line[i])) 
		{
			if(!(tmp = malloc(sizeof(t_list))))
				return (MALLOC_FAIL);
			if(!(tmp->content = ft_strdup_no_space(line + i)))
				return (MALLOC_FAIL);
			tmp->next = 0;
			ft_lstadd_back(&env->map.list, tmp);
		}
		free(line);
	}
	free(line);
	if (!env->data.R || !env->data.n || !env->data.s || !env->data.w || !env->data.e || !env->data.sp || !env->data.F || !env->data.C || !env->map.list)
		return (WRONG_INPUT);

	//path fix
	i = 0;
	while (env->data.n[i] != '.')
		i++;
	if(!(env->data.NO = ft_strdup_no_space(env->data.n + i)))
		return (MALLOC_FAIL);
	free(env->data.n);
	env->data.n = NULL;

	i = 0;
	while (env->data.s[i] != '.')
		i++;
	if(!(env->data.SO = ft_strdup_no_space(env->data.s + i)))
		return (MALLOC_FAIL);
	free(env->data.s);
	env->data.s = NULL;

	i = 0;
	while (env->data.w[i] != '.')
		i++;
	if(!(env->data.WE = ft_strdup_no_space(env->data.w + i)))
		return (MALLOC_FAIL);
	free(env->data.w);
	env->data.w = NULL;

	i = 0;
	while (env->data.e[i] != '.')
		i++;
	if(!(env->data.EA = ft_strdup_no_space(env->data.e + i)))
		return (MALLOC_FAIL);
	free(env->data.e);
	env->data.e = NULL;

	i = 0;
	while (env->data.sp[i] != '.')
		i++;
	if(!(env->data.SP = ft_strdup_no_space(env->data.sp + i)))
		return (MALLOC_FAIL);
	free(env->data.sp);
	env->data.sp = NULL;
	
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
