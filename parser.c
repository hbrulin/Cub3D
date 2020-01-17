/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:10:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/17 17:44:25 by hbrulin          ###   ########.fr       */
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
				env->pos.x = j + 0.5; 
				env->pos.y = i + 0.5;
				env->map.tab_map[i][j] = '0';
			}
			if (env->map.tab_map[i][j] == '2')
				env->nb_sprite++;
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

void	ft_free_path(char *s)
{
	free(s);
	s = NULL;
}

int	get_start_path(char *s)
{
	int i;

	i = 0;
	while (s[i] != '.')
		i++;
	return (i);
}

int		path_fix(t_env *env)
{
	int i;

	i = get_start_path(env->data.n);
	if(!(env->data.NO = ft_strtrim(env->data.n + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.n);
	i = get_start_path(env->data.s);
	if(!(env->data.SO = ft_strtrim(env->data.s + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.s);
	i = get_start_path(env->data.w);
	if(!(env->data.WE = ft_strtrim(env->data.w + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.w);
	i = get_start_path(env->data.e);
	if(!(env->data.EA = ft_strtrim(env->data.e + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.e);
	i = get_start_path(env->data.sp);
	if(!(env->data.SP = ft_strtrim(env->data.sp + i, " ")))
		return (MALLOC_FAIL);
	ft_free_path(env->data.sp);
	return (SUCCESS);
}

int		check_data(t_env *env)
{
	if (!env->data.R || !env->data.n || !env->data.s || !env->data.w ||
		!env->data.e || !env->data.sp || !env->data.F || !env->data.C ||
		!env->map.list)
		return (WRONG_INPUT);
	if(env->data.R[1] != ' ' || env->data.n[2] != ' ' || env->data.s[2] != ' ' 
		|| env->data.w[2] != ' ' || env->data.e[2] != ' ' || 
		env->data.sp[1] != ' ' || env->data.F[1] != ' ' || 
		env->data.C[1] != ' ')
		return (WRONG_INPUT);
	return (SUCCESS);
}

int get_data_three(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'F' && line[i + 1] == ' ' && *flag_map == 0 && env->data.F == NULL)
	{
		if(!(env->data.F = ft_strtrim(line + i, " ")))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'F' && line[i + 1] == ' ' && (flag_map != 0 || env->data.F != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'C' && line[i + 1] == ' ' && *flag_map == 0 && env->data.C == NULL)
	{
		if(!(env->data.C = ft_strtrim(line + i, " ")))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'C' && line[i + 1] == ' ' && (flag_map != 0 || env->data.C != NULL))
		return (WRONG_INPUT);
		return (SUCCESS);
}

int get_data_two(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'W' && line[i + 1] == 'E' && *flag_map == 0 && env->data.w == NULL)
	{
		if(!(env->data.w = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E' && (flag_map != 0 || env->data.w != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'E' && line[i + 1] == 'A' && *flag_map == 0 && env->data.e == NULL)
	{
		if(!(env->data.e = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A' && (flag_map != 0 || env->data.e != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'S' && line[i + 1] == ' ' && *flag_map == 0 && env->data.sp == NULL)
	{
		if(!(env->data.sp = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == ' ' && (flag_map != 0 || env->data.sp != NULL))
		return (WRONG_INPUT);
	if((env->error = get_data_three(env, line, i, flag_map)) != SUCCESS)
		return(env->error);
	return (SUCCESS);
}

int		get_data(t_env *env, char *line, int i, int *flag_map)
{
	if (line[i] == 'R' && *flag_map == 0 && env->data.R == NULL)
	{
		if(!(env->data.R = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'R' && (*flag_map != 0 || env->data.R != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'N' && line[i + 1] == 'O' && *flag_map == 0 && env->data.n == NULL)
	{
		if(!(env->data.n = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'N' && line[i + 1] == 'O' && (*flag_map != 0 || env->data.n != NULL))
		return (WRONG_INPUT);
	if (line[i] == 'S' && line[i + 1] == 'O' && *flag_map == 0 && env->data.s == NULL)
	{
		if(!(env->data.s = ft_strdup(line + i)))
			return (MALLOC_FAIL);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O' && (*flag_map != 0 || env->data.s != NULL))
		return (WRONG_INPUT);
	if((env->error = get_data_two(env, line, i, flag_map)) != SUCCESS)
		return(env->error);
	return (SUCCESS);
}

int		ft_read(t_env *env, int fd)
{
	int 	ret;
	char *line;
	t_list	*tmp;
	size_t i;
	static int flag_map;

	flag_map = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{	
		i = 0;
		if (ft_strncmp(line, "", 1) == 0 && flag_map != 0)
			return (WRONG_INPUT);
		while (line[i] == ' ' && line[i])
		{
			i++;
			if (i == ft_strlen(line) && flag_map != 0)
				return (WRONG_INPUT);
		}
		if (ft_isalpha(line[i]))
		{
			if((env->error = get_data(env, line, i, &flag_map)) != SUCCESS)
				return(env->error);
		}
		else if (ft_isdigit(line[i])) 
		{
			flag_map++;
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
	if((env->error = check_data(env)) != SUCCESS)
		return(env->error);
	if((env->error = path_fix(env)) != SUCCESS)
		return(env->error);
	
	return (SUCCESS);
}

int		get_map(t_env *env, char *file)
{
	int fd;
	t_list	*tmp;
	int i;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (OPEN_ERR);
	if((env->error = ft_read(env, fd)) != SUCCESS)
		return(env->error);
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
