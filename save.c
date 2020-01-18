/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:11:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 13:25:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				write_colors(t_env *env, int fd, int height, int width)
{
	static unsigned char	rgb[3] = {
		0, 0, 0 };
	int						i;
	int						j;

	i = 0;
	while (i < (int)env->height)
	{
		j = 0;
		while (j < (int)env->width)
		{
			rgb[0] = ((env->img->img_data[(height - i) * width + j]) >> 16);
			rgb[1] = ((env->img->img_data[(height - i) * width + j]) >> 8);
			rgb[2] = (env->img->img_data[(height - i) * width + j]);
			if ((write(fd, rgb + 2, 1)) < 0)
				return (WRITE_FAIL);
			if ((write(fd, rgb + 1, 1)) < 0)
				return (WRITE_FAIL);
			if ((write(fd, rgb, 1)) < 0)
				return (WRITE_FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int				ft_save(t_env *env)
{
	t_save save;

	save.height = env->height - 1;
	save.width = env->width;
	save.pad = (4 - ((int)env->width * 3) % 4) % 4;
	save.file_header = create_file_header(env, save.pad);
	save.img_header = create_img_header(save.height, save.width);
	if ((save.fd = open(SCREEN_PATH, O_WRONLY | O_CREAT, RIGHTS)) < 0)
		return (OPEN_ERR);
	if ((env->error = write_headers(&save)) != SUCCESS)
		return (env->error);
	if ((env->error = write_colors(env, save.fd, save.height, save.width))
		!= SUCCESS)
	{
		close(save.fd);
		return (env->error);
	}
	close(save.fd);
	return (SUCCESS);
}

int				launch_save(t_env *env)
{
	ft_disp_screen(env);
	if ((env->error = ft_save(env)) != SUCCESS)
		return (env->error);
	deal_exit(env);
	return (SUCCESS);
}
