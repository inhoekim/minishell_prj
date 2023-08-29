/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 11:00:33 by dasong            #+#    #+#             */
/*   Updated: 2023/04/23 11:43:53 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buff_container	buff_cont;
	t_buff_vector			buff_v;
	char					*res;
	int						eof_flag;
	int						idx;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	eof_flag = 1;
	if (!buff_cont.capacity && !init_buff(&buff_cont))
	{
		buff_cont.capacity = 0;
		return (0);
	}
	if (!search_fd(&buff_cont, fd, &buff_v, &idx) || \
	!load_buffer(fd, &buff_v, 0, 0) || \
	!return_save(&buff_v, &res, 0, &eof_flag))
	{
		move_and_free(&buff_cont, idx);
		return (0);
	}
	deep_cpy_buff_v(&buff_cont.buff_cont[idx], buff_v, 0, 0);
	if (eof_flag)
		move_and_free(&buff_cont, idx);
	return (res);
}

int	search_fd(t_buff_container *p_buff_cont, int fd, \
t_buff_vector *p_buff_v, int *p_idx)
{
	int	i;

	i = -1;
	while (++i < p_buff_cont->size)
		if (p_buff_cont->buff_cont[i].fd == fd)
			break ;
	if (i == p_buff_cont->size)
	{
		deep_cpy_buff_v(p_buff_v, \
		p_buff_cont->buff_cont[p_buff_cont->size], 0, 0);
		*p_idx = p_buff_cont->size;
		p_buff_v->fd = fd;
		p_buff_cont->size++;
		if (!chk_size_buff_cont(p_buff_cont))
			return (0);
	}
	else
	{
		deep_cpy_buff_v(p_buff_v, p_buff_cont->buff_cont[i], 0, 0);
		*p_idx = i;
	}
	return (1);
}

int	chk_size_buff_cont(t_buff_container *p_buff_cont)
{
	t_buff_vector	*n_buff_cont;
	int				i;

	if (p_buff_cont->size == p_buff_cont->capacity)
	{
		n_buff_cont = (t_buff_vector *)malloc(sizeof(t_buff_vector) * \
		p_buff_cont->capacity * 2);
		if (!n_buff_cont)
			return (0);
		i = 0;
		while (i < p_buff_cont->size)
		{
			deep_cpy_buff_v(n_buff_cont + i, p_buff_cont->buff_cont[i], 0, 0);
			free(p_buff_cont->buff_cont + i++);
		}
		while (i++ < p_buff_cont->size)
		{
			n_buff_cont->fd = -1;
			n_buff_cont->size = 0;
		}
		p_buff_cont->buff_cont = n_buff_cont;
		p_buff_cont->capacity *= 2;
	}
	return (1);
}

int	chk_size_buff_v(t_buff_vector *p_buff_v)
{
	char	*new_buff;
	int		i;

	if (p_buff_v->size == p_buff_v->capacity)
	{
		new_buff = (char *)malloc(sizeof(char) * p_buff_v->capacity * 2);
		if (!new_buff)
			return (0);
		i = 0;
		while (i < p_buff_v->size)
		{
			new_buff[i] = p_buff_v->buff_v[i];
			i++;
		}
		free(p_buff_v->buff_v);
		p_buff_v->buff_v = new_buff;
		p_buff_v->capacity *= 2;
	}
	return (1);
}

void	move_and_free(t_buff_container *p_buff_container, int idx)
{
	int	i;

	ft_vector_move(p_buff_container, idx, idx + 1, \
	p_buff_container->size - 1 - idx);
	p_buff_container->size--;
	if (!p_buff_container->size)
	{
		if (p_buff_container->capacity)
		{
			i = 0;
			while (i < p_buff_container->capacity)
			{
				free(p_buff_container->buff_cont[i].buff_v);
				p_buff_container->buff_cont[i].buff_v = 0;
				p_buff_container->buff_cont[i].size = 0;
				i++;
			}
			free(p_buff_container->buff_cont);
			p_buff_container->buff_cont = 0;
			p_buff_container->capacity = 0;
		}
	}
}
