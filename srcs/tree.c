/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:28:19 by wismith           #+#    #+#             */
/*   Updated: 2023/07/02 19:21:47 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tree.h"

/** @brief inserts a node into the tree using recursion to find 
 * 				the leaf where node will be inserted.
 * 			left node is always less than root,
 * 			right is always greater than root
*/
struct s_node	*insert(t_node	*root, t_node *node)
{
	if (!root)
		return (root = node);
	if (root->hashval > node->hashval)
		root->lChld = insert(root->lChld, node);
	else
		root->rChld = insert(root->rChld, node);
	return (root);
}

/** @brief allocates a new node with hash value passed as argument
 * 			and initializes each value before returning node.
*/
struct s_node	*newNode(unsigned long hashval)
{
	t_node	*new	= (t_node *)malloc(sizeof(t_node));
	new->hashval	= hashval;
	new->nConIn		= 0;
	new->nConOut	= 0;
	new->lChld		= NULL;
	new->rChld		= NULL;
	return (new);
}

/** @brief searches for a specific hashval stored inside the tree
 * 			using recursion to to iterate through each node.
*/
struct s_node	*search(unsigned long hashval, struct s_node *root)
{
	if (!root)
		return (root);
	if (root->hashval > hashval)
		return (search (hashval, root->lChld));
	else if (root->hashval < hashval)
		return (search (hashval, root->rChld));
	return (root);
}

/** @brief frees each node in the binary tree recursively */
void	destroyTree(struct s_node *root)
{
	if (!root)
		return ;
	destroyTree(root->lChld);
	destroyTree(root->rChld);
	free (root);
}

/** @brief prints the values stored inside of the tree
 * 			using recursion to access each node
*/
void	printValues(struct s_node *root)
{
	if (!root)
		return ;
	printValues(root->lChld);

	printf ("\nFor hashvalue: %lu\n", root->hashval);
	printf ("\tTotal Number of connections: %lu\n", root->nConIn + root->nConOut);
	printf ("\tNumber of connections incoming: %lu\n", root->nConIn);
	printf ("\tNumber of connections outgoing: %lu\n\n", root->nConOut);
	
	printValues(root->rChld);
}

/** @brief function that produces a hash number given srcs and dst ips
 * 			and port numbers.
*/
unsigned long	hash( char* srcs_ip,
						char* dst_ip,
						int srcs_ports,
						int dst_port,
						int p,
						int m )
{
	char			str[256];
	unsigned long	hashValue = 0;
	long long		p_pow = 1;
	int				i = 0;

    sprintf(str, "%s:%d:%s:%d", srcs_ip, srcs_ports, dst_ip, dst_port);
	int	n = ft_strlen(str);

	while ( i < n )
	{
		hashValue = (hashValue + (str[i] - 'a' + 1) * p_pow) % (int) (1e9 + m);
		p_pow = (p_pow * p) % (int) (1e9 + 7);
		i++;
	}
	return (hashValue);
}
