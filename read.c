/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 17:46:39 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:52:14 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		list_map(t_env *env, char *line, size_t *i, t_list *tmp)
{
	if (!(tmp->content = ft_strdup_no_space(line + *i)))
		return (MALLOC_FAIL);
	tmp->next = 0;
	ft_lstadd_back(&env->map.list, tmp);
	return (SUCCESS);
}

int		pre_check_empty(char *line, size_t *i, int *flag_map)
{
	if (ft_strncmp(line, "", 1) == 0 && *flag_map != 0)
		return (WRONG_INPUT);
	while (line[*i] == ' ' && line[*i])
	{
		*i = *i + 1;
		if (*i == ft_strlen(line) && *flag_map != 0)
			return (WRONG_INPUT);
	}
	return (SUCCESS);
}

int		stock_data(char *line, t_env *env, size_t *i, int *flag_map)
{
	t_list	*tmp;

	if (ft_isalpha(line[*i]))
	{
		if ((env->error = get_data(env, line, *i, flag_map)) != SUCCESS)
			return (env->error);
	}
	else if (ft_isdigit(line[*i]))
	{
		*flag_map = *flag_map + 1;
		if (!(tmp = malloc(sizeof(t_list))))
			return (MALLOC_FAIL);
		if ((env->error = list_map(env, line, i, tmp)) != SUCCESS)
			return (env->error);
	}
	return (SUCCESS);
}

int		ft_read(t_env *env, int fd)
{
	int				ret;
	char			*line;
	static size_t	i;
	static int		flag_map;

	flag_map = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		i = 0;
		if ((env->error = pre_check_empty(line, &i, &flag_map)) != SUCCESS)
			return (env->error);
		if ((env->error = stock_data(line, env, &i, &flag_map)) != SUCCESS)
			return (env->error);
		free(line);
	}
	free(line);
	if ((env->error = check_data(env)) != SUCCESS)
		return (env->error);
	if ((env->error = path_fix(env)) != SUCCESS)
		return (env->error);
	return (SUCCESS);
}

int		get_map(t_env *env, char *file)
{
	int		fd;
	t_list	*tmp;
	int		i;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (OPEN_ERR);
	if ((env->error = ft_read(env, fd)) != SUCCESS)
		return (env->error);
	close(fd);
	if (!(env->map.tab_map = (char**)malloc(sizeof(char *) *
		ft_lstsize(env->map.list) + 1)))
		return (MALLOC_FAIL);
	i = 0;
	tmp = env->map.list;
	while (tmp)
	{
		if (!(env->map.tab_map[i] = ft_strdup(tmp->content)))
			return (MALLOC_FAIL);
		tmp = tmp->next;
		i++;
	}
	ft_lstclear(&env->map.list, free);
	env->map.tab_map[i] = 0;
	env->map.nb_line = i;
	return (SUCCESS);
}
