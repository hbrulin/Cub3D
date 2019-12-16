/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 11:11:26 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int main(int argc, char **argv)
{
	t_map map;
	t_env env;
	int		error;
	
	map.tab_map = NULL;
	if (argc == 1)
		return (NO_MAP);
	if((error = get_map(&map, argv[1])) != SUCCESS)
		return (error);
	if((error = ft_parser(&map)) != SUCCESS)
		return (error);
	if((error = init_env(&env, &map)) != SUCCESS)
		return (error);
	//ft_new_image(&env);


/*
	int  i = 0;
	while (map.tab_map[i])
	{
		printf("%s\n", map.tab_map[i]);
		i++;
	}
	printf("%s\n", map.R);
	printf("%s\n", map.SO);
	printf("%s\n", map.WE);
	printf("%s\n", map.EA);
	printf("%s\n", map.S);
	printf("%s\n", map.F);
	printf("%s\n", map.C);
*/
	//mlx_loop(env.mlx_ptr);
    return (SUCCESS);
}
