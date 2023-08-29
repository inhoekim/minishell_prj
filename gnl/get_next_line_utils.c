/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdg <sdg@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:38:55 by dasong            #+#    #+#             */
/*   Updated: 2023/08/28 22:39:45 by sdg              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	load_buffer(int fd, t_buff_vector *p_buff_v, int buffer_s, int i)
{
	char	buff[BUFFER_SIZE + 1];

	while (1)
	{
		i = -1;
		while (++i < p_buff_v->size)
			if (p_buff_v->buff_v[i] == '\n')
				break ;
		if (i != p_buff_v->size)
			break ;
		buffer_s = read(fd, buff, BUFFER_SIZE);
		if (buffer_s <= 0)
			break ;
		buff[buffer_s] = 0;
		i = 0;
		while (i < buffer_s)
		{
			p_buff_v->buff_v[p_buff_v->size++] = buff[i++];
			if (!chk_size_buff_v(p_buff_v))
				return (0);
		}
	}
	if (buffer_s < 0)
		return (0);
	return (1);
}

int	return_save(t_buff_vector *p_buff_v, char **p_res, \
int size, int *p_eof_flag)
{
	char	*ret_line;

	while (size < p_buff_v->size && p_buff_v->buff_v[size] != '\n')
		size++;
	if (size < p_buff_v->size && p_buff_v->buff_v[size] == '\n')
	{
		*p_eof_flag = 0;
		size++;
	}
	if (size == 0)
	{
		*p_res = 0;
		p_buff_v->size = 0;
		return (1);
	}
	ret_line = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret_line)
		return (0);
	ret_line[size] = 0;
	*p_res = deep_cpy_buff_v(p_buff_v, *p_buff_v, size, ret_line);
	return (1);
}

int	init_buff(t_buff_container *p_buff_cont)
{
	int	i;

	p_buff_cont->capacity = 512;
	p_buff_cont->size = 0;
	p_buff_cont->buff_cont = (t_buff_vector *)malloc(sizeof(t_buff_vector) * \
	p_buff_cont->capacity);
	if (!p_buff_cont->buff_cont)
		return (0);
	i = -1;
	while (++i < p_buff_cont->capacity)
	{
		p_buff_cont->buff_cont[i].capacity = 1024;
		p_buff_cont->buff_cont[i].size = 0;
		p_buff_cont->buff_cont[i].fd = -1;
		p_buff_cont->buff_cont[i].buff_v = (char *)malloc(sizeof(char) * \
		p_buff_cont->buff_cont[i].capacity);
		if (!p_buff_cont->buff_cont[i].buff_v)
		{
			while (i >= 0)
				free(p_buff_cont->buff_cont[i--].buff_v);
			free(p_buff_cont->buff_cont);
			return (0);
		}
	}
	return (1);
}

int	ft_vector_move(t_buff_container	*buff_cont, \
int dst_i, int src_i, size_t len)
{
	size_t			i;
	int				flag;
	t_buff_vector	tmp;

	buff_cont->buff_cont[dst_i].size = 0;
	deep_cpy_buff_v(&tmp, buff_cont->buff_cont[dst_i], 0, 0);
	if (!(buff_cont->buff_cont + dst_i) && !(buff_cont->buff_cont + src_i))
		return (0);
	if (buff_cont->buff_cont + dst_i > buff_cont->buff_cont + src_i)
		flag = 1;
	else
		flag = 0;
	i = 0;
	while (i < len)
	{
		if (flag == 1)
			deep_cpy_buff_v(buff_cont->buff_cont + dst_i + len - 1 - i, \
			(buff_cont->buff_cont + src_i)[len - 1 - i], 0, 0);
		else
			deep_cpy_buff_v(buff_cont->buff_cont + dst_i + i, \
			(buff_cont->buff_cont + src_i)[i], 0, 0);
		i++;
	}
	deep_cpy_buff_v(&buff_cont->buff_cont[buff_cont->size - 1], tmp, 0, 0);
	return (1);
}

char	*deep_cpy_buff_v(t_buff_vector *p_dst_buff_v, \
t_buff_vector src_buff_v, int flag, char *ret_line)
{
	int	i;

	if (!flag)
	{
		p_dst_buff_v->buff_v = src_buff_v.buff_v;
		p_dst_buff_v->capacity = src_buff_v.capacity;
		p_dst_buff_v->fd = src_buff_v.fd;
		p_dst_buff_v->size = src_buff_v.size;
		return (0);
	}
	else
	{
		i = -1;
		while (++i < flag)
		{
			ret_line[i] = p_dst_buff_v->buff_v[i];
			if (p_dst_buff_v->buff_v[i] == '\n')
				break ;
		}
		i = -1;
		while (++i < (p_dst_buff_v->size - flag))
			(p_dst_buff_v->buff_v)[i] = (p_dst_buff_v->buff_v + flag)[i];
		p_dst_buff_v->size = p_dst_buff_v->size - flag;
		return (ret_line);
	}
}
