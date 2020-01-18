/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:25:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:51:31 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

unsigned char	*create_file_header(t_env *env, int pad)
{
	int						file_size;
	int						bpp;
	static unsigned char	file_header[14] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	bpp = BYTES_PER_PIX;
	file_size = 54 + (bpp * ((int)env->width + pad) *
		(int)env->height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	set_in_char(file_header + 2, file_size);
	set_in_char(file_header + 10, FILE_HEADER_SIZE + IMG_HEADER_SIZE);
	return (file_header);
}

unsigned char	*create_img_header(int height, int width)
{
	static unsigned char img_header[40] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	set_in_char(img_header, 40);
	set_in_char(img_header + 4, width);
	set_in_char(img_header + 8, height);
	img_header[12] = (unsigned char)(1);
	set_in_char(img_header + 14, COMPRESSION);
	return (img_header);
}

int				write_headers(t_save *save)
{
	if ((write(save->fd, save->file_header, FILE_HEADER_SIZE)) < 0)
	{
		close(save->fd);
		return (WRITE_FAIL);
	}
	if ((write(save->fd, save->img_header, IMG_HEADER_SIZE)) < 0)
	{
		close(save->fd);
		return (WRITE_FAIL);
	}
	return (SUCCESS);
}
