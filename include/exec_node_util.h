/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seykim <seykim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:38:34 by seykim            #+#    #+#             */
/*   Updated: 2023/08/16 14:48:00 by seykim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_NODE_UTIL_H
# define EXEC_NODE_UTIL_H

# include "minishell.h"

typedef t_bool	(*t_builtin)(char **args);
void		exec_word(t_node *node, t_context *p_ctx);
t_builtin	check_builtin(char *argv);

#endif
