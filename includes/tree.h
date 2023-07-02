/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:34:16 by wismith           #+#    #+#             */
/*   Updated: 2023/07/02 19:04:07 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef TREE_H
# define TREE_H

# include <stdlib.h>
# include <stdio.h>

# include "utils.h"

/** @brief node definition for binary tree */
typedef struct	s_node
{
	/** hash value to be stored in binary tree */
	unsigned long	hashval;

	/** @brief number of connections */
	size_t			nConIn;
	size_t			nConOut;

	struct s_node	*lChld;
	struct s_node	*rChld;
	int				height;
}	t_node;

struct s_node	*newNode(unsigned long hashval);
struct s_node	*insert(t_node	*root, t_node *node);
void			destroyTree(struct s_node *root);
void			printValues(struct s_node *root);
struct s_node	*search(unsigned long hashval, struct s_node *root);
unsigned long	hash( char* srcs_ip,
						char* dst_ip,
						int srcs_ports,
						int dst_port,
						int p,
						int m );
#endif