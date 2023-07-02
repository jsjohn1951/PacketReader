/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PacketReader.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wismith <wismith@42ABUDHABI.AE>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:38:56 by wismith           #+#    #+#             */
/*   Updated: 2023/06/07 22:29:46 by wismith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PACKETREADER_H
# define PACKETREADER_H

#include <stdio.h>

# include <fcntl.h>
# include <stdlib.h>
# include <netinet/ip.h>

# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <netinet/udp.h>

#	ifndef LINUX
# include <netinet/if_ether.h>
# else
# include <netinet/ether.h>
#endif

# include "data.h"

/** 
 * info :
 * 		1) tcpdump -ni en0 -w test.pcap - command to capture packets.
 * 		2) ctrl^c (sigint) to stop the capture.
 * 		3) tcpdump -nr test.pcap -c 2 - command to display what was captured
*/

//! Errors
void	err(char *err);

//? queue
t_list	*new_entry(char *entry);
void	push_back(t_list *list, char *entry);
t_list	*pop_first(t_list *list);

//! init
void	init_data(t_data *data);
void	destroy_mutex_(t_data *data);
void	init_mutex_(t_data *data);

//* start
void	start(t_data *data);

//? Parser
void	add_queue(t_data *data, char *s);

void	parse_pcap ( u_char *user_data,
						const struct pcap_pkthdr *pkthdr,
								const u_char *packetData );

#endif