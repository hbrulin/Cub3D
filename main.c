/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:34:56 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/10 13:55:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	check_arg(int argc)
{
	if (argc == 1)
	{
		errno = EINVAL; // est bien comme ca que ca marche, et le bon errno
		puts(strerror(errno));
		return;
	}
}

int main(int argc, char **argv)
{
    int fd;
	char *line;
	int ret;
	//int i;

	t_map map;
	map.nb_line = 0;
	map.tab_map = NULL;
	check_arg (argc);

    fd = open(argv[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
    {
        map.nb_line++;
        free(line);
    }
    free(line);
	ft_parser(&map, argv[1]);

	/*i = 0;
	while (map.tab_map[i])
	{
		printf("%s\n", map.tab_map[i]);
		i++;
	}*/


    return (0);
}
