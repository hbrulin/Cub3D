/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 16:02:55 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

int	check_arg(int argc)
{
	if (argc == 1)
	{
		errno = EINVAL; // est bien comme ca que ca marche, et le bon errno
		puts(strerror(errno)); // il faut mettre ca sur la sortie Erreur
		return (-1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	int i;

	t_map map;
	t_env env;
	map.tab_map = NULL;
	if (check_arg(argc) == -1)
		return (-1);
	get_map(&map, argv[1]);
	if(ft_parser(&map) == -1)
	{
		ft_putstr("The map is wrong\n");
		return (-1);
	}
	init_env(&env);
	ft_new_image(&env);

	i = 0;
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

	mlx_loop(env.mlx_ptr);
    return (0);
}
