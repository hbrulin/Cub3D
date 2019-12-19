/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/19 16:39:07 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int main(int argc, char **argv)
{
 	t_env env;
	t_data data;
 	int		error;
 	if (argc == 1)
 		return (NO_MAP);
 	//if general
 	if((error = get_map(&env, &data, argv[1])) != SUCCESS)
 		return (error);
 	if((error = ft_parser(&env)) != SUCCESS)
 		return (error);
 	if((error = init_env(&env, &data)) != SUCCESS)
 		return (error);
 	if((error = fill_floor_ceiling(&env, &data))!= SUCCESS)
 		return (error);
	ft_calc_dir(&env);
	ft_launch(&env);
	
 
 	/*int  i = 0;
 	while (env.map.tab_map[i])
 	{
 		printf("%s\n", env.map.tab_map[i]);
 		i++;
 	}
 	printf("%s\n", data.R);
 	printf("%s\n", data.SO);
 	printf("%s\n", data.WE);
 	printf("%s\n", data.EA);
 	printf("%s\n", data.S);
 	printf("%s\n", data.F);
 	printf("%s\n", data.C);
	printf("%c\n", env.map.player);
	printf("%i, %i\n", env.map.tab_pos[0], env.map.tab_pos[1]);*/
 

 	events(&env);
    return (SUCCESS);
}


