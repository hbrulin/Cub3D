/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:11:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 13:15:24 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	write_colors(t_env *env, int fd, int height, int width)
{
	unsigned char	rgb[3] = {0, 0, 0};
	int					i;
	int					j;

	i = 0;
	while (i < (int)env->height)
	{
		j = 0;
		while (j < (int)env->width)
		{
			rgb[0] = ((env->img->img_data[(height - i) * width + j]) >> 16);
			rgb[1] = ((env->img->img_data[(height - i) * width + j]) >> 8);
			rgb[2] = (env->img->img_data[(height - i) * width + j]);
			if((write(fd, rgb + 2, 1)) < 0)
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

static void set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

unsigned char *create_file_header(t_env *env, int pad)
{
	int file_size;
	static unsigned char	file_header[14] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	file_size = 54 + (BYTES_PER_PIX * ((int)env->width + pad) * (int)env->height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	set_in_char(file_header + 2, file_size);
	set_in_char(file_header + 10, FILE_HEADER_SIZE + IMG_HEADER_SIZE);
	return(file_header);
}

unsigned char *create_img_header(int height, int width)
{
	static unsigned char img_header[40] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	set_in_char(img_header, 40);
	set_in_char(img_header + 4, width);
	set_in_char(img_header + 8, height);
	img_header[12] = (unsigned char)(1);
	set_in_char(img_header + 14, COMPRESSION);
	return(img_header);
}

int		write_headers(t_save *save)
{
	if((write(save->fd, save->file_header, FILE_HEADER_SIZE)) < 0)
	{	
		close(save->fd);
		return (WRITE_FAIL);
	}
	if((write(save->fd, save->img_header, IMG_HEADER_SIZE)) < 0)
	{
		close(save->fd);
		return (WRITE_FAIL);
	}
	return (SUCCESS);
}

int	ft_save(t_env *env)
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

int launch_save(t_env *env)
{
	ft_disp_screen(env);
	if ((env->error = ft_save(env)) != SUCCESS)
		return(env->error);
	deal_exit(env);
	return (SUCCESS);
}
