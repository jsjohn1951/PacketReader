/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:29:17 by wismith           #+#    #+#             */
/*   Updated: 2023/06/07 23:25:38 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/data.h"
#include "../includes/utils.h"

/** @brief enters new data into queue 
 * @note will allocate a new node for linked list.
 * @note will allocate a copy of entry string to list->data.
 * @note will initialize node's next pointer to NULL.
 * @note returns pointer to newly allocated note.
*/
t_list	*new_entry(char *entry)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->data = ft_strdup(entry);
	list->next = NULL;
	return (list);
}

/** @brief function to push new entry to back of queue */
void	push_back(t_list *list, char *entry)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_entry(entry);
}

/** @brief pop's the first element in the queue linked list 
 * @brief saves pointer to next node in tmp node pointer and returns
 * 			tmp as the new front node.
*/
t_list	*pop_first(t_list *list)
{
	t_list	*tmp;

	tmp = list->next;
	if (list->data)
		free(list->data);
	free(list);
	return (tmp);
}
