/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:12:37 by seykim            #+#    #+#             */
/*   Updated: 2023/08/30 19:12:39 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../libft/libft.h"
# include "execute.h"
# include <dirent.h>
# include <errno.h>
# include "util.h"

t_list	*filename_expansion(t_list *list, t_bool glob_flag);
t_list	*make_key_list(char *str, int i);
char	*concatenate(t_list *list);
char	*parameter_expansion(char *str);
char	**path_split(char *s, char c);
void	arg_expansion(t_list *list);
int		wildcard(char *pattern, char *word, int p_idx, int w_idx);

#endif