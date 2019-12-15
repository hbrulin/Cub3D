/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 10:53:56 by hbrulin          ###   ########.fr       */
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
    int fd;
	char *line;
	int ret;
	//int i;

	t_map map;
	t_env env;
	map.nb_line = 0;
	map.tab_map = NULL;
	if (check_arg(argc) == -1)
		return (-1);

    fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0) //gnl a securiser malloc
    {
        map.nb_line++;
        free(line);
    }
    free(line);
	ft_parser(&map, argv[1]);
	if (check_map(&map) == -1)
	{
		ft_putstr("The map is wrong\n");
		return (-1);
	}
	
	init_env(&env);
	ft_new_image(&env);

	/*i = 0;
	while (map.tab_map[i])
	{
		printf("%s\n", map.tab_map[i]);
		i++;
	}*/

	mlx_loop(env.mlx_ptr);
    return (0);
}
