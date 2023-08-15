/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasong <dasong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:48:17 by dasong            #+#    #+#             */
/*   Updated: 2023/08/15 11:48:20 by dasong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STDIN 0
#define STDOUT 1

typedef struct s_context
{
	int	exit_status;
	int	fd[2];
	int	fd_close;
	int	exit_status;
}	t_context;

