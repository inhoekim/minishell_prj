/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:32:42 by dasong            #+#    #+#             */
/*   Updated: 2023/04/20 06:16:54 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buff_vector
{
	int		size;
	int		capacity;
	int		fd;
	char	*buff_v;
}	t_buff_vector;

typedef struct s_buff_container
{
	int				size;
	int				capacity;
	t_buff_vector	*buff_cont;
}	t_buff_container;

char	*get_next_line(int fd);
int		search_fd(t_buff_container *p_buff_cont, int fd, \
t_buff_vector *p_buff_v, int *p_idx);
int		chk_size_buff_cont(t_buff_container *p_buff_container);
int		chk_size_buff_v(t_buff_vector *p_buff_v);
char	*deep_cpy_buff_v(t_buff_vector *p_dst_buff_v, \
t_buff_vector src_buff_v, int flag, char *ret_line);
int		init_buff(t_buff_container *p_buff_cont);
void	move_and_free(t_buff_container *p_buff_container, int idx);

int		load_buffer(int fd, t_buff_vector *p_buff_v, int buffer_s, int i);
int		return_save(t_buff_vector *p_buff_v, \
char **p_res, int size, int *p_eof_flag);
int		ft_vector_move(t_buff_container	*buff_cont, \
int dst_i, int src_i, size_t len);

#endif