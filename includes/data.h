/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:34:53 by wismith           #+#    #+#             */
/*   Updated: 2023/07/02 19:04:21 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef DATA_H
# define DATA_H

# include <pthread.h>
# include <pcap.h>
# include <stdlib.h>

# include "tree.h"

# define bool int
# define false 0
# define true 1

/** @brief link list queue */
typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/** @brief Shared Data
 * @note m_stop -> mutex to protect reading and writing stop
 * @note m_queue -> mutex to protect reading and writing the queue
 * @note stop -> flag to kill both threads
 * @note queue -> nodes with data to be written to file
 * @note pcap -> pointer to pcap struct
*/
typedef struct s_data
{

	pthread_mutex_t	m_stop;		//! mutex for accessing stop
	pthread_mutex_t	m_queue;	//! mutex for accessing queue

	bool			stop;		//! needs a mutex lock
	t_list			*queue;		//! needs a mutex lock
	pcap_t			*pcap;		//! pcap content

	int				npcap;		//! number of pcap packages
	int				WFILE;		//! file to write data to

	t_node			*root;		//! tree map root

}	t_data;

typedef struct s_strings
{
	
	char *set;
	char *set2;
	char *res;

}	t_strings;

typedef struct s_hash
{
	char	*src_ip;
	char	*dst_ip;
	int		src_p;
	int		dst_p;
}	t_hash;

#endif